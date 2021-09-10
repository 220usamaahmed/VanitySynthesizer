/*
  ==============================================================================

    SynthVoice.h
    Created: 8 Sep 2021 10:38:20pm
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "ADSRData.h"
#include "OSCData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound*) override;
    void startNote(int midiNoteNuber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int conrollerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
    OSCData& getOscillator() { return osc; }

private:
    ADSRData adsr;

    OSCData osc;
    
    juce::dsp::Gain<float> gain;

    juce::AudioBuffer<float> synthBuffer;

    bool isPrepared{ false };
};