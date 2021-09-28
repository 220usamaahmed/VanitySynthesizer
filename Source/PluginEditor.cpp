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
    modADSR(audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE"),
    waveTypeSelector(audioProcessor.apvts)
{
    setSize (648, 648);

    backgroundImage.setImage(juce::ImageCache::getFromMemory(BinaryData::backgroundrender_png, BinaryData::backgroundrender_pngSize));

    addAndMakeVisible(backgroundImage);

    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    
    addAndMakeVisible(modADSR);

    // addAndMakeVisible(waveTypeSelector);
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
    backgroundImage.setBounds(0, 0, getWidth(), getHeight());

    juce::Rectangle<int> bounds = getBounds();
    bounds.removeFromTop(50);
    bounds.removeFromLeft(56);
    bounds.removeFromBottom(51);
    bounds.removeFromRight(51);

    osc.setBounds(
        bounds.getX(),
        bounds.getTopLeft().getY() + 31,
        bounds.getWidth(), 
        bounds.getHeight() * (1.0f / 3.0f)
    );

    adsr.setBounds(
        bounds.getX(),
        bounds.getTopLeft().getY() + 217,
        bounds.getWidth(), 
        bounds.getHeight() * (4.0f / 18.0f)
    );
    
    filter.setBounds(
        bounds.getX(),
        bounds.getTopLeft().getY() + 351,
        bounds.getWidth(),
        bounds.getHeight() * (4.0f / 18.0f)
    );
    
    modADSR.setBounds(
        bounds.getX(),
        bounds.getTopLeft().getY() + 395,
        bounds.getWidth(),
        bounds.getHeight() * (1.0f / 3.0f)
    );

    // waveTypeSelector.setBounds(0, 0, 200, 200);
}