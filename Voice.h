#pragma once
#include <Audio.h>
#include "Globals.h"
#include "AnalyzeLfoPeak.h"

class Voice {
  public:
    // Osc
    AudioSynthWaveformDc        dcNoteFreq;
    AudioSynthWaveformDc        dcOscTune1;
    AudioSynthWaveformDc        dcOscTune2;
    AudioSynthWaveformDc        dcPulseWidth;
    AudioSynthWaveformModulated osc1;
    AudioSynthWaveformModulated osc2;

    // Pitch mod
    AudioSynthWaveformDc        dcPitchEnvelope;
    AudioSynthWaveform          pitchLfo;
    AudioEffectEnvelope         pitchEnvelope;
    AnalyzeLfoPeak              lfoFreqIndicator;

    // Mixer 
    AudioSynthNoisePink         noise;
    AudioMixer4                 oscFreqControl1;
    AudioMixer4                 oscFreqControl2;
    AudioMixer4                 oscMixer;

    // Filter
    //AudioFilterStateVariable  filter;
    AudioFilterLadder           filter;
    AudioMixer4                 filterFreqControl;
    AudioSynthWaveformDc        dcFilterEnvelope;
    AudioEffectEnvelope         filterEnvelope;
    AudioSynthWaveformDc        dcFilterFreq;
    AudioSynthWaveform          cutoffLfo;
    AudioSynthWaveform          resonanceLfo;

    // Amp
    AudioEffectEnvelope         ampEnvelope;

    AudioConnection connections[25] = {
      {dcNoteFreq, 0, oscFreqControl1, 0},
      {dcNoteFreq, 0, oscFreqControl2, 0},

      {dcOscTune1, 0, oscFreqControl1, 1},
      {dcOscTune2, 0, oscFreqControl2, 1},

      {dcPitchEnvelope, pitchEnvelope},
      {pitchEnvelope, 0, oscFreqControl1, 2},
      {pitchEnvelope, 0, oscFreqControl2, 2},

      {pitchLfo, 0, oscFreqControl1, 3},
      {pitchLfo, 0, oscFreqControl2, 3},
      {pitchLfo, 0, lfoFreqIndicator, 0},

      {oscFreqControl1, 0, osc1, 0},
      {oscFreqControl2, 0, osc2, 0},
      {dcPulseWidth, 0, osc1, 1},
      {dcPulseWidth, 0, osc2, 1},

      {osc1, 0, oscMixer, 0},
      {osc2, 0, oscMixer, 1},
      {noise, 0, oscMixer, 3},

      {dcFilterEnvelope, 0, filterEnvelope, 0},
      {filterEnvelope, 0, filterFreqControl, 0},
      {dcFilterFreq, 0, filterFreqControl, 1},
      {cutoffLfo, 0, filterFreqControl, 2},

      {oscMixer, 0, filter, 0},
      {filterFreqControl, 0, filter, 1},
      {resonanceLfo, 0, filter, 2},
      {filter, 0, ampEnvelope, 0}      
    };

    AudioConnection patchCable;

    int voiceId;
    uint8_t channel = 1;
    uint8_t currentNote = 0;
    bool lfoMidiSynch = false;
    float midiPulseDuration = 20.75;
    uint8_t lfoMidiSynchDivision = 0;

    float oscMix = 0.5;
    float noiseMix = 0.0;
    float glide = 0;
    bool glideEngage = false;
    unsigned long lastUpdate;
    float prevLfoValue = 0;

    void setWaveform(AudioSynthWaveformModulated& wf, byte type) {
      switch (type) {
        case 0: wf.begin(WAVEFORM_SINE);      wf.amplitude(1); break;
        case 1: wf.begin(WAVEFORM_TRIANGLE);  wf.amplitude(1);break;
        case 2: wf.begin(WAVEFORM_SAWTOOTH);  wf.amplitude(0.5);break;
        case 3: wf.begin(WAVEFORM_SQUARE);    wf.amplitude(0.5); break;
        case 4: wf.begin(WAVEFORM_PULSE);     wf.amplitude(0.5);break;
      }      
    }

    void updateOscMix() {
      oscMixer.gain(0, (1 - oscMix) * (1 - noiseMix));
      oscMixer.gain(1, oscMix * (1 - noiseMix));
      oscMixer.gain(3, noiseMix);

      //TRACE3("Mixer: %f %f %f\n", (1 - oscMix) * (1 - noiseMix), oscMix * (1 - noiseMix), noiseMix);
    }

  public:
    Voice(int id, AudioMixer4& mixer, int pos) : 
      patchCable(ampEnvelope, 0, mixer, pos),
      voiceId(id) {
    }

    void setup() {

      dcOscTune1.amplitude(0.0);
      dcOscTune2.amplitude(0.0);
      dcNoteFreq.amplitude(0.0);
      dcPulseWidth.amplitude(0.0);
      dcPitchEnvelope.amplitude(0.0);
      dcFilterEnvelope.amplitude(0.0);

      osc1.frequencyModulation(MAX_OCTAVE);
      osc1.begin(1, NOTE_MIDI_0, WAVEFORM_BANDLIMIT_SAWTOOTH);
      osc2.frequencyModulation(MAX_OCTAVE);
      osc2.begin(1, NOTE_MIDI_0, WAVEFORM_BANDLIMIT_SAWTOOTH);

      noise.amplitude(1.0);

      pitchLfo.amplitude(0.0);
      pitchLfo.begin(WAVEFORM_SINE); //WAVEFORM_TRIANGLE);
      pitchLfo.frequency(0.0);

      cutoffLfo.begin(WAVEFORM_SINE);
      cutoffLfo.amplitude(0.0);
      cutoffLfo.frequency(0.0);

      resonanceLfo.begin(WAVEFORM_SINE);
      resonanceLfo.amplitude(0.0);
      resonanceLfo.frequency(0.0);

      filterFreqControl.gain(0, 1.0);
      filterFreqControl.gain(1, 1.0);
      filterFreqControl.gain(2, 1.0);

      filter.octaveControl(3.0);

      updateOscMix();

      pitchEnvelope.attack(0.0);
      pitchEnvelope.decay(50.0);
      pitchEnvelope.release(0.0);
      pitchEnvelope.sustain(0.0);

      filterEnvelope.attack(0.0);
      filterEnvelope.decay(50.0);
      filterEnvelope.release(0.0);
      filterEnvelope.sustain(0.0);

      ampEnvelope.attack(10);
      ampEnvelope.decay(0.0);
      ampEnvelope.sustain(1.0);
      ampEnvelope.release(500);
   }

    int id() {
      return voiceId;
    }

    void setChannel(uint8_t value) {
      channel = value;
    }

    uint8_t getChannel() {
      return channel;
    }

    bool isPlaying() {
      return currentNote != 0;
    }

    void PlayNote(byte note, byte velocity) {
      currentNote = note;

      float duration = 1.0 + (float)glideEngage * glide * MAX_GLIDE_TIME;
      float level = ((float)note /*+ 12 * transpose*/) * HALFTONE_TO_DC;

      dcNoteFreq.amplitude(level, duration);

      pitchEnvelope.noteOn();
      filterEnvelope.noteOn();
      ampEnvelope.noteOn();
    }

    void StopPlaying() {
      ampEnvelope.noteOff();
      filterEnvelope.noteOff();
      pitchEnvelope.noteOff();
      currentNote = 0;
    }

    void update() {
      if (channel == 0)
        return;

      if (millis() - lastUpdate < 500)
        return;

      if (lfoFreqIndicator.available()) {
        float lfoValue = lfoFreqIndicator.read();
        TRACE1("LFO value = ", lfoValue);
        if (lfoValue < prevLfoValue) {
          TRACE("**** LFO Peak ****")
        }

        prevLfoValue = lfoValue;
      }

      lastUpdate = millis();
    }

    void updateLfo() {
      if (!lfoMidiSynch)
        return;

      float frequency = 1 / (getPulsePerMidiDivision(lfoMidiSynchDivision) * midiPulseDuration / 1000.0);

      pitchLfo.frequency(frequency);
      cutoffLfo.frequency(frequency);
      resonanceLfo.frequency(frequency);
    }

    void setMidiPulseDuration(float value) {
      midiPulseDuration = value;
      updateLfo();
    }

    void setDetuning(float value) {
      value = value * (12 * HALFTONE_TO_DC); // +/- 1 octave
      dcOscTune2.amplitude(value);
    }

    void setFilterCutoff(float frequency) {
      dcFilterFreq.amplitude(frequency);
    }

    void setFilterResonance(float resonance) {
      filter.resonance(resonance);
    }

    void setFilterEnvAmount(float amount) {
      dcFilterEnvelope.amplitude(amount);
    }

    void setOscMix(float mix) {
      oscMix = mix;
      updateOscMix();
    }

    void setNoiseMix(float mix) {
      noiseMix = mix;
      updateOscMix();
    }

    void setOsc1Shape(byte type) {
      setWaveform(osc1, type);
    }

    void setOsc2Shape(byte type) {
      setWaveform(osc2, type);
    }

    void setPulseWidth(float value) {
      dcPulseWidth.amplitude(value);
    }

    void setAmpEnvAttack(float value) {
      ampEnvelope.attack(value);
    }

    void setAmpEnvDecay(float value) {
      ampEnvelope.decay(value);
    }
    
    void setAmpEnvSustain(float value) {
      ampEnvelope.sustain(value);
    }

    void setAmpEnvRelease(float value) {
      ampEnvelope.release(value);
    }

    void setFilterEnvAttack(float value) {
      filterEnvelope.attack(value);
    }

    void setFilterEnvDecay(float value) {
      filterEnvelope.decay(value);
    }
    
    void setFilterEnvSustain(float value) {
      filterEnvelope.sustain(value);
    }

    void setFilterEnvRelease(float value) {
      filterEnvelope.release(value);
    }

    void setPitchEnvAmount(float amount) {
      dcPitchEnvelope.amplitude(amount);
    }

    void setPitchEnvAttack(float value) {
      pitchEnvelope.attack(value);
    }

    void setPitchEnvDecay(float value) {
      pitchEnvelope.decay(value);
    }
    
    void setPitchEnvSustain(float value) {
      pitchEnvelope.sustain(value);
    }

    void setPitchEnvRelease(float value) {
      pitchEnvelope.release(value);
    }

    void setLfoShape(uint8_t value) {

      uint8_t wf = WAVEFORM_SINE;

      switch (value)
      {
        case 0: wf = WAVEFORM_SINE; break;
        case 1: wf = WAVEFORM_TRIANGLE; break;
        case 2: wf = WAVEFORM_PULSE; break;
      }

      pitchLfo.begin(wf);
      cutoffLfo.begin(wf);
      resonanceLfo.begin(wf);
    }

    void setLfoFrequency(float frequency) {
      pitchLfo.frequency(frequency);
      cutoffLfo.frequency(frequency);
      resonanceLfo.frequency(frequency);
    }

    void setLfoPitchAmount(float depth) {
      pitchLfo.amplitude(depth * (12 * HALFTONE_TO_DC));
    }

    void setLfoCutoffAmount(float depth) {
      cutoffLfo.amplitude(depth);
    }

    void setLfoResonanceAmount(float depth) {
      resonanceLfo.amplitude(depth);
    }
    
    void setLfoOsc2Modulation(bool value) {
    }

    void setLfoMidiSynch(bool value) {
      lfoMidiSynch = value;
      updateLfo();
    }

    void setLfoMidiSynchDivision(uint8_t value) {
      lfoMidiSynchDivision = value;
      updateLfo();      
    }

    void setGlideRate(float value) {
      glide = value;
    }

    void setGlideSwitch(bool value) {
      glideEngage = value;
    }

    void setGlideType(uint8_t value) {
    }
};