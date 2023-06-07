#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void SelectInputFile();
    void SelectOutputFile();
    void Run();
private:
    //==============================================================================
    // Your private member variables go here...
    juce::TextButton inputFileButton;
    juce::TextButton outputFileButton;
    juce::TextButton runButton;
    std::unique_ptr<juce::FileChooser> myChooser;
    std::string m_InputFilePath;
    std::string m_OutputFilePath;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
