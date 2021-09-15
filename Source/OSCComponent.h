/*
  ==============================================================================

    OSCComponent.h
    Created: 10 Sep 2021 10:15:40pm
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OSCComponent : public juce::Component
{
public:
    OSCComponent(juce::AudioProcessorValueTreeState& apvts);
    ~OSCComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    juce::Slider fmDepthSlider;
    juce::Slider fmFreqSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> fmDepthSliderAttachment;
    std::unique_ptr<SliderAttachment> fmFreqSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCComponent)
};
