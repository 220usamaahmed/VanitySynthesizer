/*
  ==============================================================================

    ADSRData.cpp
    Created: 10 Sep 2021 1:40:01pm
    Author:  220us

  ==============================================================================
*/

#include "ADSRData.h"

void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;

    setParameters(adsrParameters);
}