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
    juce::LookAndFeel_V4::setDefaultLookAndFeel(&customLNF);

    juce::StringArray choices{ "Sin", "Saw", "Square", "Triangle" };
    oscWaveSelector.addItemList(choices, 1);
    // addAndMakeVisible(oscWaveSelector);
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "OSC", oscWaveSelector);

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
    // This method is where you should set the bounds of any child
    // components that your component contains..

    oscWaveSelector.setBounds(0, 0, 90, 20);

    auto const oneThird = getWidth() / 3.0f;

    fmDepthSlider.setBounds(oneThird, 0, oneThird, oneThird);
    fmFreqSlider.setBounds(oneThird * 2, 0, oneThird, oneThird);
}
