#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(200, 200);
    
    globalGain.setSliderStyle(juce::Slider::LinearBarVertical);
    globalGain.setRange(0.0,100.0,0.1);
    globalGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    globalGain.setPopupDisplayEnabled(true,false,this);
    globalGain.setTextValueSuffix("%");
    globalGain.setValue(1.0);
    addAndMakeVisible(&globalGain);
    globalGain.addListener(this);
    frequencySlider.setSliderStyle(juce::Slider::LinearBarVertical);
    frequencySlider.setRange(30.0,10000.0,1.0);
    frequencySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    frequencySlider.setPopupDisplayEnabled(true,false,this);
    frequencySlider.setTextValueSuffix(" hz");
    frequencySlider.setValue(440.0);
    addAndMakeVisible(frequencySlider);
    frequencySlider.addListener(this);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("_O______", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    globalGain.setBounds (40, 30, 20, getHeight() - 60);
    frequencySlider.setBounds(70, 30, 20, getHeight() - 60);
}


void AudioPluginAudioProcessorEditor::sliderValueChanged (juce::Slider* slider) {
    if (slider == &globalGain) {
        processorRef.gain = globalGain.getValue() * 0.01;
    } else if (slider == &frequencySlider) {
        processorRef.frequency = frequencySlider.getValue();
        processorRef.updateAngleDelta();
    }
}