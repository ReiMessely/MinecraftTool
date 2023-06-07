#pragma once

#include <JuceHeader.h>
#include "TableModel.h"

namespace aze
{
    class SceneParser;
}
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
    void Read();
    void Save();
private:
    //==============================================================================
    // Your private member variables go here...
    juce::TableListBox m_DataTable;
    TableModel* m_pTableModel;

    juce::TextButton inputFileButton;
    juce::TextButton outputFileButton;
    juce::TextButton saveButton;
    juce::ToggleButton toggleOpenOutputButton;
    std::unique_ptr<juce::FileChooser> myChooser;
    std::string m_InputFilePath;
    std::string m_OutputFilePath;

    std::unique_ptr<aze::SceneParser> m_SceneParser;
    bool m_OpenFileFlag;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
