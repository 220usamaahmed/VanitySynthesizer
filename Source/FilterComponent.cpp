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
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    juce::StringArray choices{ "Lowpass", "Bandpass", "Highpass" };
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);
    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "FILTERTYPE", filterTypeSelector);

    filterFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    filterResSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterResSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    addAndMakeVisible(filterFreqSlider);
    addAndMakeVisible(filterResSlider);

    filterFreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERCUTOFF", filterFreqSlider);
    filterResSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "FILTERRES", filterResSlider);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::black);   // clear the background
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    filterTypeSelector.setBounds(0, 0, 90, 20);

    filterFreqSlider.setBounds(0, 50, 100, 100);
    filterResSlider.setBounds(150, 50, 100, 100);
}
