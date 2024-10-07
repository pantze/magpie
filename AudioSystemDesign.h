#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dcPitchEnvelope;            //xy=82,307
AudioEffectEnvelope      pitchEnvelope;      //xy=254.75,307.25
AudioSynthWaveformDc     dcOscTune1;            //xy=262.5,198.25001525878906
AudioSynthWaveformDc     dcOscTune2;            //xy=264,237.50001525878906
AudioSynthWaveformDc     dcNoteFreq;            //xy=266.25,106.25001525878906
AudioSynthWaveform       pitchLfo;      //xy=274.5,382
AudioSynthWaveformDc     dcFilterEnvelope;            //xy=412.6785659790039,478.5714383125305
AudioAnalyzePeak         lfoFreqIndicator;          //xy=555,396
AudioMixer4              oscFreqControl1;         //xy=565.7500038146973,170.7500343322754
AudioMixer4              oscFreqControl2;         //xy=566.2500038146973,261.0000190734863
AudioSynthWaveformDc     dcPulseWidth;            //xy=575.25,336.5000305175781
AudioEffectEnvelope      filterEnvelope;      //xy=611.4285659790039,477.32143926620483
AudioSynthWaveformDc     dcFilterFreq;            //xy=616.4286193847656,521.8214316368103
AudioSynthWaveform       cutoffLfo;      //xy=627.4285583496094,569.3214316368103
AudioSynthWaveformModulated osc1;   //xy=783.75,176.25
AudioSynthNoisePink      noise;          //xy=785.75,343.25
AudioSynthWaveformModulated osc2;   //xy=787,267.00001525878906
AudioMixer4              filterFreqControl;         //xy=873.6785583496094,487.3214316368103
AudioSynthWaveform       resonanceLfo;      //xy=886.1785583496094,576.3214316368103
AudioMixer4              oscMixer;         //xy=989.25,194.50001525878906
AudioFilterLadder        filter;        //xy=1164.25,207.25001525878906
AudioEffectEnvelope      ampEnvelope;      //xy=1352,206.00001525878906
AudioOutputI2S           i2s1;           //xy=1569.25,207.75
AudioConnection          patchCord1(dcPitchEnvelope, pitchEnvelope);
AudioConnection          patchCord2(pitchEnvelope, 0, oscFreqControl1, 2);
AudioConnection          patchCord3(pitchEnvelope, 0, oscFreqControl2, 2);
AudioConnection          patchCord4(dcOscTune1, 0, oscFreqControl1, 1);
AudioConnection          patchCord5(dcOscTune2, 0, oscFreqControl2, 1);
AudioConnection          patchCord6(dcNoteFreq, 0, oscFreqControl1, 0);
AudioConnection          patchCord7(dcNoteFreq, 0, oscFreqControl2, 0);
AudioConnection          patchCord8(pitchLfo, 0, oscFreqControl1, 3);
AudioConnection          patchCord9(pitchLfo, 0, oscFreqControl2, 3);
AudioConnection          patchCord10(pitchLfo, lfoFreqIndicator);
AudioConnection          patchCord11(dcFilterEnvelope, filterEnvelope);
AudioConnection          patchCord12(oscFreqControl1, 0, osc1, 0);
AudioConnection          patchCord13(oscFreqControl2, 0, osc2, 0);
AudioConnection          patchCord14(dcPulseWidth, 0, osc1, 1);
AudioConnection          patchCord15(dcPulseWidth, 0, osc2, 1);
AudioConnection          patchCord16(filterEnvelope, 0, filterFreqControl, 0);
AudioConnection          patchCord17(dcFilterFreq, 0, filterFreqControl, 1);
AudioConnection          patchCord18(cutoffLfo, 0, filterFreqControl, 2);
AudioConnection          patchCord19(osc1, 0, oscMixer, 0);
AudioConnection          patchCord20(noise, 0, oscMixer, 3);
AudioConnection          patchCord21(osc2, 0, oscMixer, 1);
AudioConnection          patchCord22(filterFreqControl, 0, filter, 1);
AudioConnection          patchCord23(resonanceLfo, 0, filter, 2);
AudioConnection          patchCord24(oscMixer, 0, filter, 0);
AudioConnection          patchCord25(filter, ampEnvelope);
AudioConnection          patchCord26(ampEnvelope, 0, i2s1, 0);
AudioConnection          patchCord27(ampEnvelope, 0, i2s1, 1);
// GUItool: end automatically generated code
