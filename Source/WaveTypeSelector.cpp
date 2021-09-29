/*
  ==============================================================================

    WaveTypeSelector.cpp
    Created: 18 Sep 2021 1:22:19am
    Author:  220us

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveTypeSelector.h"

//==============================================================================
WaveTypeSelector::WaveTypeSelector(juce::AudioProcessorValueTreeState& apvts) :
    waveTypeSelectorAttachment(*apvts.getParameter("OSC"), parameterChangedCallback)
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(&customLNF);

    sinButton.setRadioGroupId(WaveButtons);
    sawButton.setRadioGroupId(WaveButtons);
    squareButton.setRadioGroupId(WaveButtons);
    triangleButton.setRadioGroupId(WaveButtons);

    addAndMakeVisible(sinButton);
    addAndMakeVisible(sawButton);
    addAndMakeVisible(squareButton);
    addAndMakeVisible(triangleButton);
    
    sinButton.onClick = [this] { updateToggleState(&sinButton, "Sin"); };
    sawButton.onClick = [this] { updateToggleState(&sawButton, "Saw"); };
    squareButton.onClick = [this] { updateToggleState(&squareButton, "Square"); };
    triangleButton.onClick = [this] { updateToggleState(&triangleButton, "Triangle"); };

    sinButton.setToggleState(true, false);
}

WaveTypeSelector::~WaveTypeSelector()
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(nullptr);
}

void WaveTypeSelector::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentBlack);
}

void WaveTypeSelector::resized()
{
    sinButton.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    sawButton.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);
    squareButton.setBounds(0, getHeight() / 2, getWidth() / 2, getHeight() / 2);
    triangleButton.setBounds(getWidth() / 2, getHeight() / 2, getWidth() / 2, getHeight() / 2);
}

void WaveTypeSelector::updateToggleState(juce::Button* button, juce::String name)
{
    if (name.compare("Sin") == 0)
        waveTypeSelectorAttachment.setValueAsCompleteGesture(0);
    else if (name.compare("Saw") == 0)
        waveTypeSelectorAttachment.setValueAsCompleteGesture(1);
    else if (name.compare("Square") == 0)
        waveTypeSelectorAttachment.setValueAsCompleteGesture(2);
    else if (name.compare("Triangle") == 0)
        waveTypeSelectorAttachment.setValueAsCompleteGesture(3);
    else
        jassertfalse;
}

void WaveTypeSelector::parameterChangedCallback(float newValue)
{
    // TODO: Update UI here
}