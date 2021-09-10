/*
  ==============================================================================

    OSCData.cpp
    Created: 10 Sep 2021 3:12:40pm
    Author:  220us

  ==============================================================================
*/

#include "OSCData.h"

void OSCData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
}

void OSCData::setWaveType(const int choice)
{   
    switch (choice)
    {
    case 0:
        // Sin wave
        initialise([](float x) { return std::sin(x); });
        break;
    case 1:
        // Saw wave
        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
        break;
    case 2:
        // Square wave
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
        break;
    default:
        jassertfalse;
        break;
    }
}

void OSCData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OSCData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}