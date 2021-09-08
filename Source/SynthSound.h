/*
  ==============================================================================

    SynthSound.h
    Created: 8 Sep 2021 10:38:46pm
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};