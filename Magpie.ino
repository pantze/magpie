#include <Audio.h>
#include <MIDI.h>
#include "Utils.h"
#include "Globals.h"
#include "KeyboardController.h"
#include "PolySynth.h"
#include "PatchManager.h"

#define MIDI_PORT1_NAME {'M', 'K', 'V', '0' ,'1' ,' ' ,' ' ,' '}
#define MIDI_PORT1_NAME_LEN 8

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
PolySynth synth;
KeyboardController keyboard(synth);
PatchManager patchMgr;

unsigned long pulseStart = 0;
unsigned long pulseCounter = 0;

unsigned long lastMillis = 0;
unsigned long counter = 0;

void setup() {
  AudioMemory(200);

  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleProgramChange(handleProgramChange);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandlePitchBend(handlePitchBend);
  MIDI.setHandleClock(handleClock);
  MIDI.setHandleStart(handleStart);
  MIDI.setHandleContinue(handleContinue);
  MIDI.setHandleStop(handleStop);

  usbMIDI.setHandleControlChange(handleControlChange);
  usbMIDI.setHandleProgramChange(handleProgramChange);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandlePitchChange(handlePitchBend);
  usbMIDI.setHandleClock(handleClock);
  usbMIDI.setHandleStart(handleStart);
  usbMIDI.setHandleContinue(handleContinue);
  usbMIDI.setHandleStop(handleStop);
  usbMIDI.setHandleSystemExclusive(handleSystemExclusive);

  MIDI.begin();
  Serial.begin(19200);

  AudioNoInterrupts();
  synth.setup(global.channel);
  synth.setMode(PolyModes::Poly8, global.channel);
  AudioInterrupts();

  TRACE("\n");
  TRACE("---------------------------\n");
  TRACE("Welcome to PolySynth\n");
  TRACE("---------------------------\n");
  TRACE("\n");

  TRACE("Channels:\n");
  for (int i = 1; i <= MIDI_CHANNELS; i++) {
    TRACE2("Ch:%d %s\n", i, synth.channelActive(i) ? "Active" : "");
  }

  patchMgr.loadProgramSettings(global.channel, 0, & synth);
}

void loop() {
  MIDI.read();
  usbMIDI.read();
  synth.update();

  counter++;

  if (millis() - lastMillis > 2000) {
    if (AudioProcessorUsage() > 75.0) 
    {
      TRACE3("CPU(%3.2f / %3.2f) Count=%d\n", AudioProcessorUsage(), AudioProcessorUsageMax(), counter);
      lastMillis = millis();
      counter = 0;
    }
  }
}

void handleSystemExclusive(byte *data, unsigned int length) {
  //TRACE1("HandleSysEx(%d)\n", length);
  //patchMgr.receiveData(data, length);
}

void handleClock() {
  pulseCounter++;
  
  // Stabilize
  if (pulseCounter < 10)
    return;

  float pulseDuration = (micros() - pulseStart) / pulseCounter / 1000.0;
  synth.setPulseDuration(pulseDuration);
  //TRACE2("BPM: %f %f\n", pulseDuration, 60000.0 / pulseDuration / 24);
}

void handleStart() {
  pulseStart = micros();
  pulseCounter = 0;
  //TRACE("MIDI-Start\n");
}
void handleContinue() {
  //TRACE("MIDI-Continue\n");
}
void handleStop() {
  //TRACE("MIDI-Stop\n");
}

void handleNoteOn(byte channel, byte note, byte velocity) {
  if (!synth.channelActive(channel))
    return;

  keyboard.handleNoteOn(channel, note, velocity);
}

void handleNoteOff(byte channel, byte note, byte velocity) {
  if (!synth.channelActive(channel))
    return;

  keyboard.handleNoteOff(channel, note, velocity);
}

void handlePitchBend(byte channel, int pitch) {
  if (!synth.channelActive(channel))
    return;

  synth.handlePitchBend(channel, pitch);
}

void handleProgramChange(byte channel, byte program) {
  if (!synth.channelActive(channel))
    return;

  patchMgr.programChange(channel, program, & synth);
}

void handleControlChange(byte channel, byte control, byte value) {
  if (!synth.channelActive(channel))
    return;

  patchMgr.updatePatch(channel, control, value);  
  synth.handleControlChange(channel, control, value);
}
