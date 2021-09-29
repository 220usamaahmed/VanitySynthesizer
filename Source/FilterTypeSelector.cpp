/*
  ==============================================================================

    FilterTypeSelector.cpp
    Created: 30 Sep 2021 2:17:04am
    Author:  220us

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterTypeSelector.h"

//==============================================================================
FilterTypeSelector::FilterTypeSelector(juce::AudioProcessorValueTreeState& apvts) :
    filterTypeSelectorAttachment(*apvts.getParameter("FILTERTYPE"), paramerterChangedCallback)
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(&customLNF);

    noneButton.setRadioGroupId(FilterButtons);
    lowpassButton.setRadioGroupId(FilterButtons);
    bandpassButton.setRadioGroupId(FilterButtons);
    highpassButton.setRadioGroupId(FilterButtons);

    addAndMakeVisible(noneButton);
    addAndMakeVisible(lowpassButton);
    addAndMakeVisible(bandpassButton);
    addAndMakeVisible(highpassButton);

    noneButton.onClick = [this] { updateToggleState(&noneButton, "None"); };
    lowpassButton.onClick = [this] { updateToggleState(&noneButton, "Lowpass"); };
    bandpassButton.onClick = [this] { updateToggleState(&noneButton, "Bandpass"); };
    highpassButton.onClick = [this] { updateToggleState(&noneButton, "Highpass"); };

    noneButton.setToggleState(true, false);
}

FilterTypeSelector::~FilterTypeSelector()
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(nullptr);
}

void FilterTypeSelector::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentBlack);
}

void FilterTypeSelector::resized()
{
    noneButton.setBounds(0, 0, getWidth() / 4, getHeight());
    lowpassButton.setBounds(getWidth() / 4, 0, getWidth() / 4, getHeight());
    bandpassButton.setBounds(getWidth() / 2, 0, getWidth() / 4, getHeight());
    highpassButton.setBounds(getWidth() * 3.0f / 4.0f, 0, getWidth() / 4, getHeight());
}

void FilterTypeSelector::updateToggleState(juce::Button* button, juce::String name)
{
    if (name.compare("None") == 0)
        filterTypeSelectorAttachment.setValueAsCompleteGesture(0);
    else if (name.compare("Lowpass") == 0)
        filterTypeSelectorAttachment.setValueAsCompleteGesture(1);
    else if (name.compare("Bandpass") == 0)
        filterTypeSelectorAttachment.setValueAsCompleteGesture(2);
    else if (name.compare("Highpass") == 0)
        filterTypeSelectorAttachment.setValueAsCompleteGesture(3);
    else
        jassertfalse;
}

void FilterTypeSelector::paramerterChangedCallback(float newValue)
{

}