/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth_00AudioProcessorEditor::Synth_00AudioProcessorEditor (Synth_00AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    adsr(audioProcessor.apvts),
    osc(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
}

Synth_00AudioProcessorEditor::~Synth_00AudioProcessorEditor()
{
}

//==============================================================================
void Synth_00AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
}

void Synth_00AudioProcessorEditor::resized()
{
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    osc.setBounds(10, 10, 100, 30);
}