/*
  ==============================================================================

    FilterData.h
    Created: 16 Sep 2021 12:56:02pm
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterData
{
public:
    void prepareToPlay(double sampleRate, double samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int filterType, const float freq, const float resonance, const float modulator = 1.0f);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> filter;

    bool filterBypass{ true };

    bool isPrepared{ false };
};
