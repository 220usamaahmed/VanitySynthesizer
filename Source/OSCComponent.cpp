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
OSCComponent::OSCComponent(juce::AudioProcessorValueTreeState& apvts) :
    oscWaveSelector(apvts)
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(&customLNF);

    addAndMakeVisible(oscWaveSelector);

    fmDepthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmDepthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    fmFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmFreqSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    addAndMakeVisible(fmDepthSlider);
    addAndMakeVisible(fmFreqSlider);

    fmDepthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FMDEPTH", fmDepthSlider);
    fmFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FMFREQ", fmFreqSlider);
}

OSCComponent::~OSCComponent()
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(nullptr);
}

void OSCComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentBlack);
}

void OSCComponent::resized()
{
    auto const oneThird = getWidth() / 3.0f;

    oscWaveSelector.setBounds(0, 0, oneThird, oneThird);
    fmDepthSlider.setBounds(oneThird, 0, oneThird, oneThird);
    fmFreqSlider.setBounds(oneThird * 2, 0, oneThird, oneThird);
}
