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
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);

    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{    
    g.fillAll(juce::Colours::black);   // clear the background
}

void ADSRComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    const auto bounds = getLocalBounds();
    const auto sliderWidth = bounds.getWidth() / 4;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
}

void ADSRComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}