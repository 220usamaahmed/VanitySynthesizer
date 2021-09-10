/*
  ==============================================================================

    OSCComponent.cpp
    Created: 10 Sep 2021 10:15:40pm
    Author:  220us

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OSCComponent.h"

//==============================================================================
OSCComponent::OSCComponent(juce::AudioProcessorValueTreeState& apvts)
{
    juce::StringArray choices{ "Sin", "Saw", "Square" };
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "OSC", oscWaveSelector);
}

OSCComponent::~OSCComponent()
{
}

void OSCComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::black);   // clear the background
}

void OSCComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    oscWaveSelector.setBounds(0, 0, 90, 20);
}
