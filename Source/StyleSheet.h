/*
  ==============================================================================

    StyleSheet.h
    Created: 24 Sep 2021 9:45:42pm
    Author:  220us

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomLNF : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider&) override;
};
