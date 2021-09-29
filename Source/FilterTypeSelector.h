/*
  ==============================================================================

    FilterTypeSelector.h
    Created: 30 Sep 2021 2:17:04am
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StyleSheet.h"

//==============================================================================
/*
*/
class FilterTypeSelector  : public juce::Component
{
public:
    FilterTypeSelector(juce::AudioProcessorValueTreeState& apvts);
    ~FilterTypeSelector() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    enum RadioButtonIds
    {
        FilterButtons = 1002
    };

private:
    CustomLNF customLNF;

    juce::ToggleButton noneButton{ "None" };
    juce::ToggleButton lowpassButton{ "Lowpass" };
    juce::ToggleButton bandpassButton{ "Bandpass" };
    juce::ToggleButton highpassButton{ "Highpass" };

    void updateToggleState(juce::Button* button, juce::String name);

    static void paramerterChangedCallback(float newValue);
    juce::ParameterAttachment filterTypeSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterTypeSelector)
};
