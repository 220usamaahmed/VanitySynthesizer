/*
  ==============================================================================

    OSCData.h
    Created: 10 Sep 2021 3:12:40pm
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OSCData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setWaveFrequency(const int midiNoteNumber);
    void setFMParams(const float depth, const float freq);
private:
    juce::dsp::Oscillator<float> fmOsc = { [](float x) { return std::sin(x); } };
    float fmMod{ 0.0f };
    float fmDepth{ 0.0f };
    int lastMIDINote{ 0 };
};