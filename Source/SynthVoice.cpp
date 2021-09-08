/*
  ==============================================================================

    SynthVoice.cpp
    Created: 8 Sep 2021 10:38:20pm
    Author:  220us

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNuber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{

}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::controllerMoved(int conrollerNumber, int newControllerValue)
{

}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

}