/*
  ==============================================================================

    FilterData.cpp
    Created: 16 Sep 2021 12:56:02pm
    Author:  220us

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, double samplesPerBlock, int numChannels)
{
    filter.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    filter.prepare(spec);

    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    if (!filterBypass)
    {
        juce::dsp::AudioBlock<float> block{ buffer };
        filter.process(juce::dsp::ProcessContextReplacing<float>{ block });
    }
}

void FilterData::updateParameters(const int filterType, const float freq, const float resonance, const float modulator)
{
    filterBypass = false;

    switch (filterType)
    {
    case 0:
        filterBypass = true;
    case 1:
        filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    case 2:
        filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;
    case 3:
        filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
    }

    float modFreq = std::fmax(std::fmin(freq * modulator, 20000.0f), 20.0f);

    filter.setCutoffFrequency(modFreq);
    filter.setResonance(resonance);
}

void FilterData::reset()
{
    filter.reset();
}