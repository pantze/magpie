#pragma once
#include "Globals.h"

static const int MAX_PATCHES = 16;

// BEGIN-PATCH-DUMP
Patch patches[MAX_PATCHES] = {
    // Patch 0
    {
        "Epiano",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 64}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 0}, // FilterResonance
            {22, 64}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 14}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 64}, // Osc1Shape
            {71, 64}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 1
    {
        "Phaser",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 60}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 0}, // FilterResonance
            {22, 95}, // FilterEnvAmount
            {23, 11}, // FilterEnvAttack
            {24, 0}, // FilterEnvDecay
            {25, 0}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 14}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 84}, // Osc1Shape
            {71, 84}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 2
    {
        "Boxy organ",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 65}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 39}, // FilterResonance
            {22, 65}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 14}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 127}, // Osc1Shape
            {71, 127}, // Osc2Shape
            {72, 110}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 3
    {
        "Clean epiano",
       {
            {15, 88}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 58}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 60}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 0}, // FilterResonance
            {22, 65}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 0}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 22}, // Osc1Shape
            {71, 48}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 4
    {
        "Funky synth",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 64}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 29}, // FilterResonance
            {22, 65}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 0}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 64}, // Osc1Shape
            {71, 64}, // Osc2Shape
            {72, 61}, // PulseWidth
            {75, 62}, // LfoMode
            {76, 0}, // LfoShape
            {3, 58}, // LfoFrequency
            {12, 61}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 127}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 5
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 65}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 0}, // FilterResonance
            {22, 65}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 0}, // AmpEnvAttack
            {29, 37}, // AmpEnvDecay
            {30, 67}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 127}, // Osc1Shape
            {71, 64}, // Osc2Shape
            {72, 93}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 127}, // LfoShape
            {3, 61}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 127}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 127}, // LfoKeyTrigger
            {86, 72}, // LfoMidiSynchDivision
            {87, 127}, // LfoMidiSynch
            {112, 127}  // LfoOsc2Modulation
    }},
    // Patch 6
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 65}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 39}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 38}, // FilterResonance
            {22, 0}, // FilterEnvAmount
            {23, 0}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 41}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 0}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 33}, // Osc1Shape
            {71, 85}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 7
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 65}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 15}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 32}, // FilterResonance
            {22, 127}, // FilterEnvAmount
            {23, 32}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 14}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 0}, // Osc1Shape
            {71, 34}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 8
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 58}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 65}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 25}, // FilterResonance
            {22, 71}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 0}, // AmpEnvAttack
            {29, 56}, // AmpEnvDecay
            {30, 41}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 127}, // Osc1Shape
            {71, 85}, // Osc2Shape
            {72, 86}, // PulseWidth
            {75, 58}, // LfoMode
            {76, 0}, // LfoShape
            {3, 62}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 41}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 124}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 9
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 58}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 20}, // FilterResonance
            {22, 102}, // FilterEnvAmount
            {23, 28}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 0}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 85}, // Osc1Shape
            {71, 64}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 105}, // LfoFrequency
            {12, 127}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 10
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 60}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 52}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 34}, // FilterResonance
            {22, 17}, // FilterEnvAmount
            {23, 24}, // FilterEnvAttack
            {24, 0}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 28}, // AmpEnvAttack
            {29, 48}, // AmpEnvDecay
            {30, 44}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 0}, // Osc1Shape
            {71, 34}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 11
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 55}, // NoiseMix (0-127 Osc-Noise)
            {17, 65}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 39}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 0}, // FilterResonance
            {22, 93}, // FilterEnvAmount
            {23, 0}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 0}, // AmpEnvAttack
            {29, 30}, // AmpEnvDecay
            {30, 0}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 89}, // Osc1Shape
            {71, 0}, // Osc2Shape
            {72, 36}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 104}, // LfoFrequency
            {12, 51}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 12
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 19}, // NoiseMix (0-127 Osc-Noise)
            {17, 0}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 39}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 72}, // FilterResonance
            {22, 75}, // FilterEnvAmount
            {23, 13}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 0}, // AmpEnvAttack
            {29, 20}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 0}, // Osc1Shape
            {71, 36}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 65}, // LfoMode
            {76, 0}, // LfoShape
            {3, 50}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 94}, // LfoPitchAmount
            {14, 71}, // LfoResonanceAmount
            {82, 127}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 13
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 65}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 0}, // FilterResonance
            {22, 65}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 14}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 64}, // Osc1Shape
            {71, 64}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 14
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 65}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 0}, // FilterResonance
            {22, 65}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 14}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 64}, // Osc1Shape
            {71, 64}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }},
    // Patch 15
    {
        "empty",
       {
            {15, 64}, // OscMix (0-127 Osc1-Osc2)
            {16, 0}, // NoiseMix (0-127 Osc-Noise)
            {17, 65}, // Detune (0-127 / 64 center +/- 1 octave)
            {19, 64}, // FilterCutoff (0-127 0-10000 Hz)
            {21, 0}, // FilterResonance
            {22, 65}, // FilterEnvAmount
            {23, 10}, // FilterEnvAttack
            {24, 43}, // FilterEnvDecay
            {25, 22}, // FilterEnvSustain
            {26, 0}, // FilterEnvRelease
            {28, 14}, // AmpEnvAttack
            {29, 25}, // AmpEnvDecay
            {30, 127}, // AmpEnvSustain
            {31, 0}, // AmpEnvRelease
            {32, 64}, // PitchEnvAmount
            {33, 0}, // PitchEnvAttack
            {34, 0}, // PitchEnvDecay
            {35, 0}, // PitchEnvSustain
            {36, 0}, // PitchEnvRelease            
            {70, 64}, // Osc1Shape
            {71, 64}, // Osc2Shape
            {72, 65}, // PulseWidth
            {75, 0}, // LfoMode
            {76, 0}, // LfoShape
            {3, 0}, // LfoFrequency
            {12, 0}, // LfoCutoffAmount
            {13, 0}, // LfoPitchAmount
            {14, 0}, // LfoResonanceAmount
            {82, 0}, // LfoKeyTrigger
            {86, 0}, // LfoMidiSynchDivision
            {87, 0}, // LfoMidiSynch
            {112, 0}  // LfoOsc2Modulation
    }} 
}; // patches
// END-PATCH-DUMP

