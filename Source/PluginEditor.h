/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_C50CF82AAD28CB69__
#define __JUCE_HEADER_C50CF82AAD28CB69__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GainPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Timer,
                                        public SliderListener
{
public:
    //==============================================================================
    GainPluginAudioProcessorEditor (GainPluginAudioProcessor* ownerFilter);
    ~GainPluginAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    GainPluginAudioProcessor* getProcessor() const {return static_cast<GainPluginAudioProcessor*>(
        getAudioProcessor());}
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* palmtree_png;
    static const int palmtree_pngSize;
    static const char* sand_png;
    static const int sand_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
//    ScopedPointer<Slider> slider3;
//    ScopedPointer<Label> label3;
//    ScopedPointer<Label> label4;
//    ScopedPointer<Label> label5;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> gainslider;
    ScopedPointer<Slider> thresholdslider;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Slider> ratioslider;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> title;
    ScopedPointer<Slider> attackslider;
    ScopedPointer<Slider> releaseslider;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label5;
    Image cachedImage_palmtree_png_1;
    Image cachedImage_sand_png_2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPluginAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_C50CF82AAD28CB69__
