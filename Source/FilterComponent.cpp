/*
  ==============================================================================

    FilterComponent.cpp
    Created: 16 Sep 2021 2:57:20pm
    Author:  220us

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts) :
    filterTypeSelector(apvts)
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(&customLNF);

    addAndMakeVisible(filterTypeSelector);
    
    filterFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterFreqSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    filterResSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterResSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(filterFreqSlider);
    addAndMakeVisible(filterResSlider);

    filterFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERCUTOFF", filterFreqSlider);
    filterResSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERRES", filterResSlider);
}

FilterComponent::~FilterComponent()
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(nullptr);
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentBlack);
}

void FilterComponent::resized()
{
    const auto bounds = getLocalBounds();

    auto const oneSixth = bounds.getWidth() / 6.0f;

    filterTypeSelector.setBounds(0, 10, oneSixth * 4, oneSixth);
    filterFreqSlider.setBounds(oneSixth * 4, 0, oneSixth, oneSixth);
    filterResSlider.setBounds(oneSixth * 5, 0, oneSixth, oneSixth);
}
