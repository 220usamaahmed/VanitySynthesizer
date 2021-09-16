/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth_00AudioProcessor::Synth_00AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    apvts(*this, nullptr, "PARAMTERS", createParameters())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

Synth_00AudioProcessor::~Synth_00AudioProcessor()
{
}

//==============================================================================
const juce::String Synth_00AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Synth_00AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Synth_00AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Synth_00AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Synth_00AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Synth_00AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Synth_00AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Synth_00AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Synth_00AudioProcessor::getProgramName (int index)
{
    return {};
}

void Synth_00AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Synth_00AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void Synth_00AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth_00AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Synth_00AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            auto& oscWave = *apvts.getRawParameterValue("OSC");
            
            auto& fmDepth = *apvts.getRawParameterValue("FMDEPTH");
            auto& fmFreq = *apvts.getRawParameterValue("FMFREQ");

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& filterCutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
            auto& filterRes = *apvts.getRawParameterValue("FILTERRES");

            auto& modAttack = *apvts.getRawParameterValue("MODATTACK");
            auto& modDecay = *apvts.getRawParameterValue("MODDECAY");
            auto& modSustain = *apvts.getRawParameterValue("MODSUSTAIN");
            auto& modRelease = *apvts.getRawParameterValue("MODRELEASE");

            voice->getOscillator().setWaveType(oscWave);
            voice->getOscillator().setFMParams(fmDepth, fmFreq);
            voice->updateADSR(attack.load(), decay.load(), sustain.load(), release.load());
            voice->updateFilter(filterType.load(), filterCutoff.load(), filterRes.load());
            voice->updateModADSR(modAttack.load(), modDecay.load(), modSustain.load(), modRelease.load());
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Synth_00AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Synth_00AudioProcessor::createEditor()
{
    return new Synth_00AudioProcessorEditor (*this);
}

//==============================================================================
void Synth_00AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Synth_00AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Synth_00AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Synth_00AudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Wave type
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", 
        juce::StringArray{ "Sin", "Saw", "Square"}, 0));

    // FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FMFREQ", "FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 1.0f }, 5.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FMDEPTH", "FM Depth", juce::NormalisableRange<float> { 0.0f, 100.0f, 1.0f }, 500.0f));

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));

    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type",
        juce::StringArray{ "Lowpass", "Bandpass", "Highpass" }, 0));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 20.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "FILTERRES", "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f));

    // Filter ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "MODATTACK", "Mod Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "MODDECAY", "Mod Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "MODSUSTAIN", "Mod Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "MODRELEASE", "Mod Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));

    return { params.begin(), params.end() };
}