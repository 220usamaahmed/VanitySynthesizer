/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ADSRComponent.h"
#include "OSCComponent.h"
#include "FilterComponent.h"

//==============================================================================
/**
*/
class Synth_00AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Synth_00AudioProcessorEditor (Synth_00AudioProcessor&);
    ~Synth_00AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    Synth_00AudioProcessor& audioProcessor;

    OSCComponent osc;
    ADSRComponent adsr;
    FilterComponent filter;
    ADSRComponent modADSR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth_00AudioProcessorEditor)
};
