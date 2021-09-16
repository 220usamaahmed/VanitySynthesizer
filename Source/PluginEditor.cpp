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
    adsr(audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    osc(audioProcessor.apvts),
    filter(audioProcessor.apvts),
    modADSR(audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);
    addAndMakeVisible(filter);
    addAndMakeVisible(modADSR);
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
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);
    osc.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    filter.setBounds(0, getHeight() / 2, getWidth() / 2, getHeight() / 2);
    modADSR.setBounds(getWidth() / 2, getHeight() / 2, getWidth() / 2, getHeight() / 2);
}