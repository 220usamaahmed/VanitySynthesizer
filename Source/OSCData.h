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
private:

};