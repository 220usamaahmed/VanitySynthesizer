/*
  ==============================================================================

    StyleSheet.cpp
    Created: 24 Sep 2021 9:45:42pm
    Author:  220us

  ==============================================================================
*/

#include "StyleSheet.h"


void CustomLNF::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    auto outline = juce::Colour::Colour(24, 24, 24);
    auto fill = juce::Colour::Colour(255, 73, 99);

    auto bounds = juce::Rectangle<int>(x, y + 24, width, height).toFloat().reduced(12);

    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmin(2.0f, radius * 0.5f);
    auto arcRadius = (radius > 70) ? (radius - (lineW * 0.5f)) * 0.85f : (radius - (lineW * 0.5f)) * 0.95f;
    auto markerRadius = (radius > 70) ? arcRadius * 0.65f : arcRadius * 0.50f;
    auto markerAngle = toAngle - juce::MathConstants<float>::pi / 2;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc(bounds.getCentreX(),
        bounds.getCentreY() - 16,
        arcRadius,
        arcRadius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);

    g.setColour(outline);
    g.strokePath(backgroundArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY() - 16,
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            toAngle,
            true);

        g.setColour(fill);
        g.strokePath(valueArc, juce::PathStrokeType(lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
        g.setColour(juce::Colour(196, 196, 196));
        g.fillEllipse(
            bounds.getCentreX() + markerRadius * cos(markerAngle),
            bounds.getCentreY() - 16 + markerRadius * sin(markerAngle),
            4, 4);
    }

    auto value = juce::String(slider.getValue());
    auto strWidth = g.getCurrentFont().getStringWidth(value);
    juce::Rectangle<float> r;
    r.setTop(y);
    r.setBottom(y + 24);
    r.setLeft(x);
    r.setRight(x + width);
    g.setColour(juce::Colours::white);
    g.drawFittedText(value, r.toNearestInt(), juce::Justification::centred, 1);
}