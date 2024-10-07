#pragma once
#include "Utils.h"
#include "Globals.h"
#include "PolySynth.h"
#include "Patches.h"

class PatchManager {
  private:
    uint8_t patchBuffer[127];
    bool dirtyBuffer[MIDI_CHANNELS + 1][127];
    int currentProgram[MIDI_CHANNELS + 1];

  private:
    void saveCurrentProgram(uint8_t channel) {
      TRACE2("(CH-%d) Saving prg=%d\n", channel, currentProgram[channel]);
      
      for (int i = 0; i < NUM_PATCH_SETTINGS; i++) {
        uint8_t cc = PatchSettingsCC[i];
        bool isDirty = dirtyBuffer[channel][cc];

        if (!isDirty)
          continue;

        //TRACE4("Saving %d # cc=%d, %s, value=%d\n", i, cc, PatchSettingsT[i], patchBuffer[cc]);
        patches[currentProgram[channel]].settings[i].control = cc;
        patches[currentProgram[channel]].settings[i].value = patchBuffer[cc];
        dirtyBuffer[channel][cc] = false;
      }
    }

  public:
    void updatePatch(uint8_t channel, uint8_t control, uint8_t value) {
      if (control == MidiControlMessage::DumpPatches) {
        dumpAll(channel);
        return;
      }

      patchBuffer[control] = value;
      dirtyBuffer[channel][control] = true;
    }

    void programChange(uint8_t channel, uint8_t program, PolySynth* synth) {
      if (program >= MAX_PATCHES)
        return;

      TRACE2("ProgramChange(Ch%d %d)\n", channel, program);

      if (program == currentProgram[channel])
        return;

      saveCurrentProgram(channel);
      currentProgram[channel] = program;
      loadProgramSettings(channel, program, synth);
    }

    void loadProgramSettings(uint8_t channel, uint8_t program, PolySynth* synth) {
      currentProgram[channel] = program;

      // Load program
      TRACE2("BEGIN PROGRAM CHANGE (Ch%d/%d)\n", channel, program);
      for (int i = 0; i < NUM_PATCH_SETTINGS; i++) {

        uint8_t cc = patches[currentProgram[channel]].settings[i].control;
        uint8_t value = patches[currentProgram[channel]].settings[i].value;

        //TRACE2("  CC(%d)=%d\n", cc, value);
        usbMIDI.sendControlChange(cc, value, channel);
        synth->handleControlChange(channel, cc, value);
      }
      TRACE1("END PROGRAM CHANGE (%d)\n", program);
    }

    void dumpAll(uint8_t channel) {

      saveCurrentProgram(channel);

      Serial.println("// BEGIN-PATCH-DUMP");
      Serial.println("Patch patches[MAX_PATCHES] = {");

      for (int i = 0; i < MAX_PATCHES; i++) {
        Serial.printf("    // Patch %d\n", i);
        Serial.println("    {");
        Serial.printf("        \"%s\",\n", patches[i].name);
        Serial.println("       {");
        for (int j = 0; j < NUM_PATCH_SETTINGS; j++) {
          printControlValue(j, patches[i].settings[j], j == NUM_PATCH_SETTINGS - 1);
          delay(1);
        }

        Serial.printf("    }}%c\n", (i == MAX_PATCHES - 1) ? ' ' : ',');
        Serial.flush();
        delay(1);
      }
      Serial.println("}; // patches");
      Serial.println("// END-PATCH-DUMP");
    }

    void printControlValue(int i, PatchSetting& setting, bool last) {
      if (i < 0 || i > NUM_PATCH_SETTINGS) {
        Serial.println("ERROR");
        return;
      }
      Serial.printf("            {%d, %d}%c // %s\n", setting.control, setting.value, last ? ' ' : ',', PatchSettingsT[i]);
    }

    void sendAll() {
      uint32_t length = sizeof(Patch) * MAX_PATCHES;
      uint8_t buffer[16384];

      memcpy(buffer, patches, length);    

      TRACE1("Send len=%d\n", length);
      usbMIDI.sendSysEx(length, buffer);
      TRACE("Send complete\n");
    }

    void receiveData(byte *data, unsigned int length) {
      length -= 2; // Remove start and end bytes
      data++;

      if (length < sizeof(Patch) || length % sizeof(Patch) != 0) {
        TRACE2("Failed to receive data: len=%d mod=%d\n", length, length % sizeof(Patch));
        return;
      }

      memcpy(patches, data, length);

      for (int i = 0; i < MAX_PATCHES; i++) {
        //TRACE4("Patch#%d: wf=%d dt=%d f=%d\n", i, patches[i].Osc1Waveform, patches[i].Detune, patches[i].FilterEGAmount);
      }

      TRACE1("Received %d patches\n", length / sizeof(Patch));
    }
};