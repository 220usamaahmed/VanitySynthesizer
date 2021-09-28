/*
  ==============================================================================

    WaveTypeSelector.h
    Created: 18 Sep 2021 1:22:19am
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveTypeSelector  : public juce::Component
{
public:
    WaveTypeSelector(juce::AudioProcessorValueTreeState& apvts);
    ~WaveTypeSelector() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    enum RadioButtonIds
    {
        WaveButtons = 1001
    };

private:
    juce::ToggleButton sinButton{ "Sin" };
    juce::ToggleButton squareButton{ "Square" };
    juce::ToggleButton sawButton{ "Saw" };
    juce::ToggleButton triangleButton{ "Triangle" };

    void updateToggleState(juce::Button* button, juce::String name);

    static void parameterChangedCallback(float newValue);
    juce::ParameterAttachment waveTypeSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveTypeSelector)
};
