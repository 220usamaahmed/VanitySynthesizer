/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 10 Sep 2021 1:49:41pm
    Author:  220us

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackID, juce::String decayID, juce::String sustainID, juce::String releaseID)
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(&customLNF);

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    attackAttachment = std::make_unique<SliderAttachment>(apvts, attackID, attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, decayID, decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, sustainID, sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, releaseID, releaseSlider);

    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
}

ADSRComponent::~ADSRComponent()
{
    juce::LookAndFeel_V4::setDefaultLookAndFeel(nullptr);
}

void ADSRComponent::paint (juce::Graphics& g)
{    
    g.fillAll(juce::Colours::transparentBlack);
}

void ADSRComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    const auto bounds = getLocalBounds();
    const auto sliderWidth = bounds.getWidth() / 6;
    const auto sliderHeight = bounds.getWidth() / 6;
    const auto sliderStartX = bounds.getWidth() / 3.0f;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
}

void ADSRComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(slider);
}