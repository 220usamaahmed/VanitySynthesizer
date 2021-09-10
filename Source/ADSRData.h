/*
  ==============================================================================

    ADSRData.h
    Created: 10 Sep 2021 1:40:01pm
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ADSRData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParameters;
};