#include "MainComponent.h"

MainComponent::~MainComponent()
{
}
//==============================================================================
MainComponent::MainComponent()
    :m_InputFilePath{}
    ,m_OutputFilePath{}
{
    setSize (600, 400);
    inputFileButton.setButtonText("Select input file");
    addAndMakeVisible(inputFileButton);
    inputFileButton.onClick = [this]()
    {
        SelectInputFile();
    };

    outputFileButton.setButtonText("Select output file");
    addAndMakeVisible(outputFileButton);
    outputFileButton.onClick = [this]()
    {
        SelectOutputFile();
    };

    runButton.setButtonText("Run");
    addAndMakeVisible(runButton);
    runButton.onClick = [this]()
    {
        Run();
    };
    runButton.setEnabled(false);
}
void MainComponent::SelectInputFile()
{
    using namespace juce;
    myChooser = std::make_unique<FileChooser>(
        "Please select the json file you want to load...",
        File::getSpecialLocation(File::userHomeDirectory),
        "*.json");
    auto folderChooserFlags = FileBrowserComponent::openMode;
    myChooser->launchAsync(folderChooserFlags,
        [this](const FileChooser& chooser)
        {
            juce::Logger::getCurrentLogger()->writeToLog("File selected");
			File file = chooser.getResult();
            m_InputFilePath = file.getFullPathName().toStdString();
            runButton.setEnabled(!m_InputFilePath.empty() && !m_OutputFilePath.empty());
        }
    );
}

void MainComponent::SelectOutputFile()
{
    using namespace juce;
    myChooser = std::make_unique<FileChooser>(
        "Please select the output file you want to use...",
        File::getSpecialLocation(File::userHomeDirectory),
        "*.obj");
    auto folderChooserFlags = FileBrowserComponent::openMode;
    myChooser->launchAsync(folderChooserFlags,
        [this](const FileChooser& chooser)
        {
            juce::Logger::getCurrentLogger()->writeToLog("File selected");
            File file = chooser.getResult();
            m_OutputFilePath = file.getFullPathName().toStdString();
            runButton.setEnabled(!m_InputFilePath.empty() && !m_OutputFilePath.empty());
        }
    );
}

void MainComponent::Run()
{
    
}

void MainComponent::resized()
{
    inputFileButton.setBounds(10,10,150,30);
    outputFileButton.setBounds(10, 50, 150, 30);
    runButton.setBounds(10, 90, 50, 30);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}


