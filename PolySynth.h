#pragma once
#include <Audio.h>
#include <math.h>
#include "Globals.h"
#include "Voice.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const static int NUMBER_OF_VOICES = 4;

#define FOR_ALL_VOICES(cmd) \
  for (int i = 0; i < NUMBER_OF_VOICES; i++) { \
    voices[i].cmd; \
  }

#define FOR_ALL_CHANNEL_VOICES(channel, cmd) \
  for (int i = 0; i < NUMBER_OF_VOICES; i++) { \
    if (voices[i].getChannel() == channel) voices[i].cmd; \
  }

class PolySynth {
  private:
      AudioControlSGTL5000  sgtl5000_1;
      AudioOutputI2S        i2s1;
      AudioMixer4           outputMixer;
      AudioMixer4           voiceGroup1;
      AudioMixer4           voiceGroup2;

      Voice voices[NUMBER_OF_VOICES] = {
        {1, voiceGroup1, 0},        
        {2, voiceGroup1, 1},        
        {3, voiceGroup1, 2},        
        {4, voiceGroup1, 3}/*,
        {5, voiceGroup2, 0},        
        {6, voiceGroup2, 1},        
        {7, voiceGroup2, 2},        
        {8, voiceGroup2, 3}  */    
      };

      AudioConnection connections[4] = {
        {voiceGroup1, 0, outputMixer, 0},
        {voiceGroup2, 0, outputMixer, 1},
        {outputMixer, 0, i2s1, 0},
        {outputMixer, 0, i2s1, 1}
      };

      int polyMode;
      int channelVoiceLimit[MIDI_CHANNELS + 1];
      bool glideSwitch[MIDI_CHANNELS + 1];

  public:
      void setup(uint8_t channel) {
        sgtl5000_1.enable();
        sgtl5000_1.volume(0.5);

/*        voiceGroup1.gain(0, 0.25);
        voiceGroup1.gain(1, 0.25);
        voiceGroup1.gain(2, 0.25);
        voiceGroup1.gain(3, 0.25);

        voiceGroup2.gain(0, 0.25);
        voiceGroup2.gain(1, 0.25);
        voiceGroup2.gain(2, 0.25);
        voiceGroup2.gain(3, 0.25);

        outputMixer.gain(0, 0.5);
        outputMixer.gain(1, 0.5);
*/
        FOR_ALL_VOICES(setup());
        FOR_ALL_VOICES(setFilterCutoff(3000.0));
      }

      void update() {
        FOR_ALL_VOICES(update());
      }

      void setMode(uint8_t value, uint8_t channel) {

        // Clear channel voice count
        for (int i = 1; i < MIDI_CHANNELS + 1; i++) {
          channelVoiceLimit[i] = 0;
        }

        switch (value) {
          case PolyModes::Mono:
            voices[0].setChannel(channel);
            channelVoiceLimit[channel] = 1;

            for (int i = 1; i < NUMBER_OF_VOICES; i++) {
              voices[i].setChannel(0);
            }
            break;
          case PolyModes::Poly8:
            channelVoiceLimit[channel] = NUMBER_OF_VOICES;

            for (int i = 0; i < NUMBER_OF_VOICES; i++) {
              voices[i].setChannel(channel);
            }
            break;
          case PolyModes::Multi8:
            for (int i = 0; i < NUMBER_OF_VOICES; i++) {
              voices[i].setChannel(channel + i);
              channelVoiceLimit[channel + i] = 1;
            }
            break;
          case PolyModes::Multi3p5:
            voices[0].setChannel(channel);
            voices[1].setChannel(channel);
            voices[3].setChannel(channel);
            channelVoiceLimit[channel] = 3;

            for (int i = 3; i < NUMBER_OF_VOICES; i++) {
              voices[i].setChannel(channel + (i - 2));
              channelVoiceLimit[channel + (i - 2)] = 1;
            }
            break;
        }

        polyMode = value;
      }

      bool channelActive(uint8_t channel) {
        if (channel < 1)
          return false;

        if (channel > MIDI_CHANNELS)
          return false;

        return channelVoiceLimit[channel] > 0;
      }
      
      Voice* allocateVoice(uint8_t channel) {
        Voice* nextAvailableVoice = NULL;
        int numActiveVoices = 0;
        int maxVoices = (glideSwitch[channel] == true) ? 1 : channelVoiceLimit[channel];
        
        //TRACE4("AllocateVoice: Ch:%d, max=%d/%d, mode=%d\n", channel, maxVoices, channelVoiceLimit[channel], polyMode);

        // Figure out how many voices are available and if we
        // have reached the maximum count for that channel
        for (int i = 0; i < NUMBER_OF_VOICES; i++) {
          if (voices[i].getChannel() != channel)
            continue;

          if (voices[i].isPlaying())
            numActiveVoices++;
          else
            nextAvailableVoice = &voices[i];
        }

        if (numActiveVoices < maxVoices && nextAvailableVoice != NULL) {
          nextAvailableVoice->setChannel(channel);
          return nextAvailableVoice;
        }

        TRACE1("(Ch:%d) *** No available voices for channel\n", channel);
        return NULL;
      }

      void releaseVoice(Voice* voice) {
        if (voice == NULL) {
          TRACE("*** ERROR voice is NULL\n");
          return;
        }

        voice->StopPlaying();
      }

      void setPulseDuration(float value) {
        FOR_ALL_VOICES(setMidiPulseDuration(value));
      }

      void handlePitchBend(byte channel, int pitch) {
        //TRACE2("HandlePitchBend(%d, %d)\n", channel, pitch)
      }
      
      void handleControlChange(byte channel, byte control, byte value) {
        //TRACE3("ControlChange(Ch=%d CC=%d Val=%d)\n", channel, control, value);
        float fvalue = value * DIV127;

        switch (control)
        {
          case MidiControlMessage::Volume:
            sgtl5000_1.volume(fvalue);
            TRACE2("(Ch:%d) CC-Volume: %f\n", channel, fvalue);
            break;
          case MidiControlMessage::Detune:
            fvalue = pow((fvalue * 2) - 1, 3);
            TRACE2("(Ch:%d) CC-Detune: %f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setDetuning(fvalue));
            break;
          case MidiControlMessage::FilterCutoff:
            fvalue = pow(fvalue, 2);
            TRACE2("(Ch:%d) CC-FilterCutoff: %f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setFilterCutoff(fvalue));
            break;
          case MidiControlMessage::FilterResonance:
            fvalue = 2 * fvalue;
            TRACE2("(Ch:%d) CC-FilterResonance=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setFilterResonance(fvalue));
            break;
          case MidiControlMessage::FilterEnvAmount:
            fvalue = pow(fvalue * 2 - 1, 3); // -1.0 to 1.0
            TRACE2("(Ch:%d) CC-FilterEnvAmount=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setFilterEnvAmount(fvalue));
            break;
          case MidiControlMessage::OscMix:
            TRACE2("(Ch:%d) CC-OscMix=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setOscMix(fvalue));
            break;
          case MidiControlMessage::NoiseMix:
            TRACE2("(Ch:%d) CC-NoiseMix=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setNoiseMix(fvalue));
            break;
          case MidiControlMessage::Osc1Shape:
            value = value * 0.03937;
            TRACE2("(Ch:%d) CC-Osc1Shape=%d\n", channel, value);
            FOR_ALL_CHANNEL_VOICES(channel, setOsc1Shape(value));
            break;
          case MidiControlMessage::Osc2Shape:
            value = value * 0.03937;
            TRACE2("(Ch:%d) CC-Osc2Shape=%d\n", channel, value);
            FOR_ALL_CHANNEL_VOICES(channel, setOsc2Shape(value));
            break;
          case MidiControlMessage::PulseWidth:
            TRACE2("(Ch:%d) CC-PulseWidth=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setPulseWidth(fvalue));
            break;
          case MidiControlMessage::AmpEnvAttack:
            fvalue = 3000.0 * pow(fvalue, 2.0) + 1;
            TRACE2("(Ch:%d) CC-AmpEnvAttack=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setAmpEnvAttack(fvalue));
            break;
          case MidiControlMessage::AmpEnvDecay:
            fvalue = 3000.0 * pow(fvalue, 2) + 1;
            TRACE2("(Ch:%d) CC-AmpEnvDecay=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setAmpEnvDecay(fvalue));
            break;
          case MidiControlMessage::AmpEnvRelease:
            fvalue = 3000.0 * pow(fvalue, 2) + 1;
            TRACE2("(Ch:%d) CC-AmpEnvRelease=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setAmpEnvRelease(fvalue));
            break;
          case MidiControlMessage::AmpEnvSustain:
            TRACE2("(Ch:%d) CC-AmpEnvSustain=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setAmpEnvSustain(fvalue));
            break;
          case MidiControlMessage::FilterEnvAttack:
            fvalue = 3000 * pow(fvalue, 2) + 1;
            TRACE2("(Ch:%d) CC-FilterEnvAttack=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setFilterEnvAttack(fvalue));
            break;
          case MidiControlMessage::FilterEnvDecay:
            fvalue = 3000 * pow(fvalue, 2) + 1;
            TRACE2("(Ch:%d) CC-FilterEnvDecay=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setFilterEnvDecay(fvalue));
            break;
          case MidiControlMessage::FilterEnvRelease:
            fvalue = 3000 * pow(fvalue, 2) + 1;
            TRACE2("(Ch:%d) CC-FilterEnvRelease=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setFilterEnvRelease(fvalue));
            break;
          case MidiControlMessage::FilterEnvSustain:
            TRACE2("(Ch:%d) CC-FilterEnvSustain=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setFilterEnvSustain(fvalue));
            break;
          case MidiControlMessage::PitchEnvAmount:
            fvalue = fvalue*2.0 - 1.0;
            //fvalue = pow(fvalue * 2 - 1, 3); // -1.0 to 1.0
            TRACE2("(Ch:%d) CC-PitchEnvAmount=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setPitchEnvAmount(fvalue));
            break;
          case MidiControlMessage::PitchEnvAttack:
            fvalue = 3000 * pow(fvalue, 2) + 1;
            TRACE2("(Ch:%d) CC-PitchEnvAttack=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setPitchEnvAttack(fvalue));
            break;
          case MidiControlMessage::PitchEnvDecay:
            fvalue = 3000 * pow(fvalue, 2) + 1;
            TRACE2("(Ch:%d) CC-PitchEnvDecay=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setPitchEnvDecay(fvalue));
            break;
          case MidiControlMessage::PitchEnvRelease:
            fvalue = 3000 * pow(fvalue, 2) + 1;
            TRACE2("(Ch:%d) CC-PitchEnvRelease=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setPitchEnvRelease(fvalue));
            break;
          case MidiControlMessage::PitchEnvSustain:
            TRACE2("(Ch:%d) CC-PitchEnvSustain=%f\n", channel, fvalue);
            FOR_ALL_CHANNEL_VOICES(channel, setPitchEnvSustain(fvalue));
            break;
          case MidiControlMessage::LfoShape:
            value = value * 0.023622; // 0 == Sine, 1 == Triangle, 2 = Pulse
            FOR_ALL_CHANNEL_VOICES(channel, setLfoShape(value));
            TRACE2("(Ch:%d) CC-LfoShape: %d\n", channel, value);
            break;
          case MidiControlMessage::LfoMidiSynch:
            value = value / 64; // on-off
            FOR_ALL_CHANNEL_VOICES(channel, setLfoMidiSynch(value == 1));
            TRACE2("(Ch:%d) CC-LfoMidiSynch: %d\n", channel, value);
            break;
          case MidiControlMessage::LfoMidiSynchDivision:
            value = value * 0.165354; // 0-20
            FOR_ALL_CHANNEL_VOICES(channel, setLfoMidiSynchDivision(value));
            TRACE2("(Ch:%d) CC-LfoMidiSynchDivision: %d\n", channel, value);
            break;
          case MidiControlMessage::LfoOsc2Modulation:
            value = value / 64; // on-off
            FOR_ALL_CHANNEL_VOICES(channel, setLfoOsc2Modulation(value == 1));
            TRACE2("(Ch:%d) CC-LfoOsc2Modulation: %d\n", channel, value);
            break;
          case MidiControlMessage::LfoFrequency:
            fvalue = pow(fvalue, 3) * 100; // 0-100 Hz
            FOR_ALL_CHANNEL_VOICES(channel, setLfoFrequency(fvalue));
            TRACE2("(Ch:%d) CC-LfoFrequency=%f\n", channel, fvalue);
            break;
          case MidiControlMessage::LfoPitchAmount:
            fvalue = pow(fvalue, 3);
            FOR_ALL_CHANNEL_VOICES(channel, setLfoPitchAmount(fvalue));
            TRACE2("(Ch:%d) CC-LfoPitchAmount=%f\n", channel, fvalue);
            break;
          case MidiControlMessage::LfoCutoffAmount:
            FOR_ALL_CHANNEL_VOICES(channel, setLfoCutoffAmount(fvalue * 2));
            TRACE2("(Ch:%d) CC-LfoCutoffAmount=%f\n", channel, fvalue);
            break;
          case MidiControlMessage::LfoResonanceAmount:
            FOR_ALL_CHANNEL_VOICES(channel, setLfoResonanceAmount(fvalue));
            TRACE2("(Ch:%d) CC-LfoResonanceAmount: %f\n", channel, fvalue);
            break;
          case MidiControlMessage::GlideRate:
            FOR_ALL_CHANNEL_VOICES(channel, setGlideRate(fvalue));
            TRACE2("(Ch:%d) CC-GlideRate: %f\n", channel, fvalue);
            break;
          case MidiControlMessage::GlideSwitch:
            value = value / 64;
            FOR_ALL_CHANNEL_VOICES(channel, setGlideSwitch(value == 1));
            TRACE2("(Ch:%d) CC-GlideSwitch: %d\n", channel, value);
            glideSwitch[channel] = (value == 1);
            break;
          case MidiControlMessage::GlideType:
            value = value / 42.33;
            FOR_ALL_CHANNEL_VOICES(channel, setGlideType(value));
            TRACE2("(Ch:%d) CC-GlideType: %d\n", channel, value);
            break;
          default:
            TRACE3("(Ch:%d) Unhandled CC command (CC:%d/%d\n", channel, control, value);
        }
      }    
};