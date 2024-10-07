#pragma once
#include "Globals.h"
#include "Voice.h"
#include "PolySynth.h"

struct PressedKey {
  uint8_t channel = 1;
  uint8_t note = 0;
  uint8_t velocity;
  bool isPressed;
  Voice* pVoice;
};

const static int KEY_BUFFER_SIZE = 16;

class KeyboardController {
  private:
    PolySynth& synth;
    PressedKey keyBuffer[KEY_BUFFER_SIZE];
    int latestKey = -1;

    int previousIndex(int index) {
      index--;
      return (index >= 0) ? index : KEY_BUFFER_SIZE - 1;
    }

    int nextIndex(int index) {
      index++;
      return (index < KEY_BUFFER_SIZE) ? index : 0;
    }

    int findOldestPlayingKey(uint8_t channel) {
      if (latestKey == -1)
        return -1;
      
      int oldestKey = nextIndex(latestKey);
      for (int i = 0; i < KEY_BUFFER_SIZE; i++) {
        if (keyBuffer[oldestKey].channel == channel && keyBuffer[oldestKey].isPressed && keyBuffer[oldestKey].pVoice != NULL)
          return oldestKey;

        oldestKey = nextIndex(oldestKey);
      }
      
      return -1;
    }

    int findNextFreeKey() {
      int nextFreeSlot = nextIndex(latestKey);

      // Find next free slot that isn't pressed
      for (int i = 0; i < KEY_BUFFER_SIZE; i++) {
        if (!keyBuffer[nextFreeSlot].isPressed)
          return nextFreeSlot;

        nextFreeSlot = nextIndex(nextFreeSlot);
      }

      return -1;
    }

    void dumpKeyBuffer() {
      TRACE("--- BEGIN ---\n");
      for (int i = 0; i < KEY_BUFFER_SIZE; i++) {
        if (latestKey == i) TRACE("->") else TRACE("  ");
        TRACE5("%d: Ch:%d Note:%d Pressed:%d Voice:%d", i, keyBuffer[i].channel, keyBuffer[i].note, keyBuffer[i].isPressed, keyBuffer[i].pVoice);
        if (keyBuffer[i].pVoice != NULL)
          TRACE1("VoiceId:%d", keyBuffer[i].pVoice->id());
        TRACE("\n");
      }
      TRACE("--- END ---\n");
    }

  public:
    KeyboardController(PolySynth& s) : synth(s) {
    }

    void handleNoteOn(byte channel, byte note, byte velocity) {
      //TRACE3("HandleNoteOn(%d, %d, %d)\n", channel, note, velocity)
      if ( note > 5 && note < 108 ) {
        PushNote(channel, note, velocity);
      }
    }

    void handleNoteOff(byte channel, byte note, byte velocity) {
      //TRACE3("HandleNoteOff(%d, %d, %d)\n", channel, note, velocity)
      if ( note > 5 && note < 108 ) {
        PopNote(channel, note);
      }      
    }

    void PushNote(uint8_t channel, byte note, byte velocity) {

      Voice* newVoice = synth.allocateVoice(channel);

      // No available voices? Find oldest playing key and release its voice
      if (newVoice == NULL) {
        int oldestKey = findOldestPlayingKey(channel);
        if (oldestKey == -1) {
          TRACE1("(Ch:%d) ERROR: Faled to allocate key without any key pressed\n", channel);
          dumpKeyBuffer();
        }

        keyBuffer[oldestKey].pVoice->StopPlaying();
        keyBuffer[oldestKey].pVoice = NULL;
        //TRACE3("** Silence(%d, %d, %d)\n", oldestKey, keyBuffer[oldestKey].note, keyBuffer[oldestKey].pVoice);
        newVoice = synth.allocateVoice(channel);
      }

      if (newVoice == NULL) {
        TRACE("ERROR: Failed to allocate voice\n");
        dumpKeyBuffer();
        return;
      }

      latestKey = findNextFreeKey();

      keyBuffer[latestKey].channel = channel;
      keyBuffer[latestKey].note = note;
      keyBuffer[latestKey].velocity = velocity;
      keyBuffer[latestKey].isPressed = true;
      keyBuffer[latestKey].pVoice = newVoice;
      keyBuffer[latestKey].pVoice->PlayNote(note, velocity);

      //TRACE2("PlayNote=%d Voice=%d\n", note, keyBuffer[latestKey].pVoice->id);
    }

    void PopNote(uint8_t channel, byte note) {
      // Remove key pressed for the channel
      for (int i = 0; i < KEY_BUFFER_SIZE; i++) {
        if (keyBuffer[i].channel != channel)
          continue;

        if (keyBuffer[i].note != note)
          continue;

        if (!keyBuffer[i].isPressed)
          continue;

        // Clear the key
        keyBuffer[i].channel = 0;
        keyBuffer[i].note = 0;
        keyBuffer[i].isPressed = false;

        if (keyBuffer[i].pVoice == NULL)
          return;

        //TRACE3(".  ***StopPlaying(%d, %d, %d)\n", note, keyBuffer[i].note, keyBuffer[i].pVoice);
        keyBuffer[i].pVoice->StopPlaying();
        keyBuffer[i].pVoice = NULL;

        // Find oldest key which is still pressed but has no voice?
        int oldestKey = latestKey;
        for (int i = 0; i < KEY_BUFFER_SIZE; i++) {
          oldestKey = nextIndex(oldestKey);

          PressedKey& previous = keyBuffer[oldestKey];
          if (previous.note == 0 || previous.channel != channel || !previous.isPressed)
            continue;

          if (previous.pVoice != NULL)
            continue;

          previous.pVoice = synth.allocateVoice(channel);
          previous.pVoice->PlayNote(previous.note, previous.velocity);
          //TRACE2("**Restore key note (%d) / Voice=%d\n", previous.note, previous.pVoice->id);
          delay(10);
          break;
        }

        break;
      }
    }
};
