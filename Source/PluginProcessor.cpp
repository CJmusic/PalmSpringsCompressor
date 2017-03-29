/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>  


//==============================================================================
GainPluginAudioProcessor::GainPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    UserParams[Gain] = 0.0; //THIS IS WHERE TO PUT THE USER PARAMETERS initial values - CZ
    UserParams[Threshold] = 0.0;
    UserParams[Ratio] = 1.0;
    UserParams[Attack] = 5.0;
    UserParams[Release] = 100.0;
}
GainPluginAudioProcessor::~GainPluginAudioProcessor()
{
}

//==============================================================================

// below are all things I added for the Gain parameter, probably modify them for other parameters too
const String GainPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double GainPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
int GainPluginAudioProcessor::getNumParameters()
{
    return totalNumParam;
}
float GainPluginAudioProcessor::getParameter (int index)
{
    switch(index)
    {
        case Gain:// gain is index 0
            return UserParams[Gain];
            
        case Threshold:
            return UserParams[Threshold];
            
        case Ratio:
            return UserParams[Ratio];
            
        case Attack:
            return UserParams[Attack];
            
        case Release:
            return UserParams[Release];
        default: return 0.0f;
    }
}

void GainPluginAudioProcessor::setParameter (int index, float newValue)
{
    switch(index)
    {
        case Gain:
            UserParams[Gain] = newValue;
            break;
            
        case Threshold:
            UserParams[Threshold] = newValue;
            break;
            
        case Ratio:
            UserParams[Ratio] = newValue;
            break;
            
            
        case Attack:
            UserParams[Attack] = newValue;
            break;
            
        case Release:
            UserParams[Release] = newValue;
            break;
        
            
        default: return;
    }
}
const String GainPluginAudioProcessor::getParameterName(int index)
{
    return String();
}
const String GainPluginAudioProcessor::getParameterText(int index)
{
    switch(index)
    {
        case Gain:
            return String(UserParams[Gain],3); //no idea what the 3 is for, maybe # of digits displayed?
            break;
            
        case Threshold:
            return String(UserParams[Threshold],3);
            break;
            
        case Ratio:
            return String(UserParams[Ratio],3);
            break;
            
        case Attack:
            return String(UserParams[Attack],3);
            break;
            
        case Release:
            return String(UserParams[Release],3);
            break;
        default: break;
    }
}

// this ends the the stuff I added for gain -CZ


int GainPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String GainPluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void GainPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GainPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GainPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void GainPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
//THIS IS WHERE I PUT ALL THE AUDIO PROCESSING
{
//    int numberOfChannels = getNumInputChannels();
    int numberOfChannels = 2;
    
    if (numberOfChannels == 2)
    {
        float* samples0 = buffer.getWritePointer(0);
        float* samples1 = buffer.getWritePointer(1);
    }
    
        float* samples0 = buffer.getWritePointer(0);
        float* samples1 = buffer.getWritePointer(1);
    
        bool attack(false);
        
        float x_L;
        float x_R;
        float x_LdB;
        float x_RdB;
        
        float y_L;
        float y_R;
        
        float wet(0);
        
        int t_att(0);
        int t_rel(0);
        
        float dry_LdB;
        float dry_RdB;
        
        float wet_LdB;
        float wet_RdB;
        
        int fs(getSampleRate());
        
        int numSamples = buffer.getNumSamples();
        float RMS = buffer.getRMSLevel(0, 0, numSamples);
        
        
        while (numSamples > 0)
        {
            
            x_L = *samples0;
            x_R = *samples1;
            
            x_LdB = 20.f*log10(std::abs(x_L));
            x_RdB = 20.f*log10(std::abs(x_R));
            
            
             if (x_LdB > UserParams[Threshold] || x_RdB > UserParams[Threshold]) {
                 attack = true;
                }
            
            if (attack == true) {
                if (t_att < (UserParams[Attack]/1000.f)*fs){
                    t_rel = 0;
                    t_att++;
                    wet = (float)t_att/((UserParams[Attack]/1000.f)*fs);
                }
            }
                    else {
                        wet = 1.0;
                        attack = false;
                    }

                if (attack == false){
                    if (t_rel < (UserParams[Release]/1000.0)*fs){
                        t_att--;
                        t_rel++;
                    }
                    wet = 1.0 - (float)(t_rel)/((UserParams[Release]/1000.0)*fs);
                }

                
            
            if (wet > 1.0) {
                wet = 1.0;
                attack = false;
                t_att = 0;
            }
            if (wet < 0.0) {
                wet = 0.0;
                t_rel = 0;
            }
            
            
            
        
            dry_LdB = x_LdB;
            dry_RdB = x_RdB;
                
            wet_LdB = UserParams[Threshold] + ((x_LdB - UserParams[Threshold])/UserParams[Ratio]);
            wet_RdB = UserParams[Threshold] + ((x_RdB - UserParams[Threshold])/UserParams[Ratio]);
                
            
            y_L = ((x_L > 0.0) - (x_L < 0.0))*pow(10.f,(wet_LdB*wet + dry_LdB*(1.f-wet) + UserParams[Gain])/20.0);
            y_R = ((x_R > 0.0) - (x_R < 0.0))*pow(10.f,(wet_RdB*wet + dry_RdB*(1.f-wet) + UserParams[Gain])/20.0) ;
            
            

            *samples0 = y_L;
            *samples1 = y_R;
            
            *samples0++;
            *samples1++;
            numSamples --;
        }
    
//    if (numberOfChannels == 1)
//    {
//        float* samples0 = buffer.getWritePointer(0);
//        float* samples1 = buffer.getWritePointer(0);
//        
//        int numSamples = buffer.getNumSamples();
//        
//        while (numSamples > 0) // iterating through the samples!!!! And just multiplying it by the gain!!!! - CZ
//        {
//            
////            *samples0++ *= UserParams[Gain]; WORKING
////            *samples1++ *= UserParams[Gain];
//            
//            
//            *samples0++ *= UserParams[Gain];
//            *samples1++ *= UserParams[Gain];
//            
//            numSamples --;
//            
//        }
//    }
    
    for (int i = 2; i < 2; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples()); //Causing noise
    }
    
}

//==============================================================================
bool GainPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GainPluginAudioProcessor::createEditor()
{
    return new GainPluginAudioProcessorEditor (this);
}

//==============================================================================
void GainPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainPluginAudioProcessor();
}
