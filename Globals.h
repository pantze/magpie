#pragma once
#include <Audio.h>

const float DIV127 = (1.0 / 127.0);
const float DIV64 = (1.0 / 64);

const int NUM_PATCH_SETTINGS = 33;
const int MIDI_CHANNELS = 16;

const uint8_t MAX_OCTAVE = 10;
const float MAX_GLIDE_TIME = 10000;
const float NOTE_MIDI_0 = 8.1757989156434;
const float HALFTONE_TO_DC = (float)1 / (MAX_OCTAVE * 12);

//const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

enum MidiControlMessage : uint8_t {
  GlideRate             = 5,
  GlideSwitch           = 65,
  GlideType             = 92,
  Volume                = 7,
  PolyMode              = 90,
  DumpPatches           = 119,

  // Settings
  OscMix                = 15,
  NoiseMix              = 16,
  Detune                = 17,
  FilterCutoff          = 19,
  FilterResonance       = 21,
  FilterEnvAmount       = 22,
  FilterEnvAttack       = 23,
  FilterEnvDecay        = 24, // coupled with Release
  FilterEnvSustain      = 25,
  FilterEnvRelease      = 26,
  AmpEnvAttack          = 28,
  AmpEnvDecay           = 29, // couple with Release
  AmpEnvSustain         = 30,
  AmpEnvRelease         = 31,
  PitchEnvAmount        = 32,
  PitchEnvAttack        = 33,
  PitchEnvDecay         = 34,
  PitchEnvSustain       = 35,
  PitchEnvRelease       = 36,
  Osc1Shape             = 70,
  Osc2Shape             = 71,
  PulseWidth            = 72,
  LfoMode               = 75,
  LfoShape              = 76,
  LfoFrequency          = 3,
  LfoCutoffAmount       = 12,
  LfoPitchAmount        = 13,
  LfoResonanceAmount    = 14,
  LfoKeyTrigger         = 82,
  LfoMidiSynchDivision  = 86,
  LfoMidiSynch          = 87,
  LfoOsc2Modulation     = 112
};

const MidiControlMessage PatchSettingsCC[NUM_PATCH_SETTINGS] = {
  MidiControlMessage::OscMix,
  MidiControlMessage::NoiseMix,
  MidiControlMessage::Detune,
  MidiControlMessage::FilterCutoff,
  MidiControlMessage::FilterResonance,
  MidiControlMessage::FilterEnvAmount,
  MidiControlMessage::FilterEnvAttack,
  MidiControlMessage::FilterEnvDecay,
  MidiControlMessage::FilterEnvSustain,
  MidiControlMessage::FilterEnvRelease,
  MidiControlMessage::AmpEnvAttack,
  MidiControlMessage::AmpEnvDecay,
  MidiControlMessage::AmpEnvSustain,
  MidiControlMessage::AmpEnvRelease,
  MidiControlMessage::PitchEnvAmount,
  MidiControlMessage::PitchEnvAttack,
  MidiControlMessage::PitchEnvDecay,
  MidiControlMessage::PitchEnvSustain,
  MidiControlMessage::PitchEnvRelease,
  MidiControlMessage::Osc1Shape,
  MidiControlMessage::Osc2Shape,
  MidiControlMessage::PulseWidth,
  MidiControlMessage::LfoMode,
  MidiControlMessage::LfoShape,
  MidiControlMessage::LfoFrequency,
  MidiControlMessage::LfoCutoffAmount,
  MidiControlMessage::LfoPitchAmount,
  MidiControlMessage::LfoResonanceAmount,
  MidiControlMessage::LfoKeyTrigger,
  MidiControlMessage::LfoMidiSynchDivision,
  MidiControlMessage::LfoMidiSynch,
  MidiControlMessage::LfoOsc2Modulation
};

const char* PatchSettingsT[NUM_PATCH_SETTINGS] = {
  "OscMix (0-127 Osc1-Osc2)",
  "NoiseMix (0-127 Osc-Noise)",
  "Detune (0-127 / 64 center +/- 1 octave)",
  "FilterCutoff (0-127 / 0-10000 Hz)",
  "FilterResonance (0-127 level)",
  "FilterEnvAmount (0-127 / +/- 5 octave)",
  "FilterEnvAttack (0-127 / 1-3000 ms)",
  "FilterEnvDecay (0-127 / 1-3000 ms)",
  "FilterEnvSustain (0-127 level)",
  "FilterEnvRelease (0-127 / 1-3000 ms)",
  "AmpEnvAttack (0-127 / 1-3000 ms)",
  "AmpEnvDecay (0-127 / 1-3000 ms)",
  "AmpEnvSustain (0-127 / level)",
  "AmpEnvRelease (0-127 / 1-3000 ms)",
  "PitchEnvAmount",
  "PitchEnvAttack",
  "PitchEnvDecay",
  "PitchEnvSustain",
  "PitchEnvRelease",
  "Osc1Shape (0-25 / Sine, 25-50 / Triangle, 50-75 / Sawtooth, 75-100 / Square, 100-127 Pulse)",
  "Osc2Shape (0-25 / Sine, 25-50 / Triangle, 50-75 / Sawtooth, 75-100 / Square, 100-127 Pulse)",
  "PulseWidth (0-127 / width",
  "LfoMode",
  "LfoShape",
  "LfoFrequency",
  "LfoCutoffAmount",
  "LfoPitchAmount",
  "LfoResonanceAmount",
  "LfoKeyTrigger",
  "LfoMidiSynchDivision",
  "LfoMidiSynch",
  "LfoOsc2Modulation"
};

enum PolyModes : uint8_t {
  Mono          = 0,
  Poly8         = 1,
  Multi8        = 2,
  Multi3p5      = 3
};

enum LfoModes : uint8_t {
  Free          = 0,
  Up            = 1,
  Down          = 2
};

enum GlideType : uint8_t {
  LinearConstantRate  = 0, // LCR - Linear Constant Rate
  LinearConstantTime  = 1 // LCT - Linear Constant Time
};

struct PatchSetting {
  uint8_t control = 0;
  uint8_t value = 0;
};

struct Patch {
  const char* name;
  PatchSetting settings[NUM_PATCH_SETTINGS];    
};

float getPulsePerMidiDivision(uint8_t value) {
  switch (value) {
    case 20: return 1.5;  break; // 1/64 Note
    case 19: return 1;    break; //	1/32 Note Triplet
    case 18: return 3;    break; //	1/32 Note
    case 17: return 2;    break; //	1/16 Note Triplet
    case 16: return 6;    break; //	1/16 Note
    case 15: return 4;    break; //	1/8 Note Triplet
    case 14: return 9;    break; //	Dotted 1/16 Note
    case 13: return 12;   break; //	1/8 Note
    case 12: return 8;    break; //1/4 Note Triplet
    case 11: return 18;   break; //	Dotted 1/8 Note
    case 10: return 24;   break; //	1/4 Note
    case 9:  return 16;   break; //	1/2 Note Triplet
    case 8:  return 36;   break; //	Dotted 1/4 Note
    case 7:  return 48;   break; //	1/2 Note
    case 6:  return 32;   break; //	Whole Note Triplet
    case 5:  return 60;   break; //	Dotted 1/2 Note
    case 4:  return 96;   break; //	Whole Note
    case 3:  return 144;  break; //	Whole Note + Half Note
    case 2:  return 192;  break; // 2 Whole Notes
    case 1:  return 288;  break; // 3 Whole Notes
    case 0:  return 384;  break; // 4 Whole Notes
    default: return 24;
  }
}

struct Globals {
  uint8_t channel = 1;
};

static Globals global;
