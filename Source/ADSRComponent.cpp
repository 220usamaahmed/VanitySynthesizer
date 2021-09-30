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

    attackSlider.onValueChange = [this] { repaint(); };
    decaySlider.onValueChange = [this] { repaint(); };
    sustainSlider.onValueChange = [this] { repaint(); };
    releaseSlider.onValueChange = [this] { repaint(); };

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

    // ADSR Graph
    juce::Rectangle<float> bounds(
        0, 0, getLocalBounds().getWidth() / 3.0f, getLocalBounds().getHeight()
    );
    bounds.removeFromTop(42); 
    bounds.removeFromBottom(24);
    bounds.removeFromLeft(16);
    bounds.removeFromRight(14);
    
    // g.setColour(juce::Colour(240, 240, 240));
    // g.drawRect(bounds);

    const auto p1x = bounds.getBottomLeft().getX();
    const auto p1y = bounds.getBottom();

    const auto a = attackSlider.getValue();
    const auto b = bounds.getWidth() / 4;

    const auto p2x = (bounds.getWidth() / 5.f) * attackSlider.getValue();
    const auto p2y = bounds.getTopLeft().getY();

    const auto p3x = (bounds.getWidth() / 5.f) * decaySlider.getValue();
    const auto p3y = bounds.getTopLeft().getY() + (bounds.getBottom() - (double)bounds.getTopLeft().getY()) * (1.f - sustainSlider.getValue());

    const auto p4x = bounds.getBottomRight().getX() - (bounds.getWidth() / 5.f) * releaseSlider.getValue();
    const auto p4y = p3y;

    const auto p5x = bounds.getBottomRight().getX();
    const auto p5y = bounds.getBottom();

    g.setColour(juce::Colour(148, 148, 148));
    juce::Path adsrPath;
    adsrPath.startNewSubPath(p1x, p1y);
    adsrPath.lineTo(p1x + p2x, p2y);
    adsrPath.lineTo(p1x + p2x + p3x, p3y);
    adsrPath.lineTo(p4x, p4y);
    adsrPath.lineTo(p5x, p5y);
    g.strokePath(adsrPath, juce::PathStrokeType(2.f));

    g.setColour(juce::Colour(255, 73, 99));
    g.fillEllipse(p1x - 4, p1y - 4, 8, 8);
    g.fillEllipse(p1x + p2x - 4, p2y - 4, 8, 8);
    g.fillEllipse(p1x + p2x + p3x - 4, p3y - 4, 8, 8);
    g.fillEllipse(p4x - 4, p4y - 4, 8, 8);
    g.fillEllipse(p5x - 4, p5y - 4, 8, 8);
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