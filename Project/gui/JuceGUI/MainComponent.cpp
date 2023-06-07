#include "MainComponent.h"
#include <utility>
#include "../../commoncode/SceneParser.h"
#include "../../commoncode/Utils.h"
#include <Windows.h>


MainComponent::~MainComponent()
{
    delete m_pTableModel;
}
//==============================================================================
MainComponent::MainComponent()
    :m_InputFilePath{}
    ,m_OutputFilePath{}
    ,m_OpenFileFlag{false}
{
    m_SceneParser = std::make_unique<aze::SceneParser>();

    setSize (600, 400);

    // Table
    addAndMakeVisible(m_DataTable);
    m_pTableModel = new TableModel();
    m_DataTable.setModel(m_pTableModel);
    m_DataTable.getHeader().addColumn("BlockType", 1, 100, 50, 200);
    m_DataTable.getHeader().addColumn("x", 2, 50, 20, 60);
    m_DataTable.getHeader().addColumn("y", 3, 50, 20, 60);
    m_DataTable.getHeader().addColumn("z", 4, 50, 20, 60);

    //
    toggleOpenOutputButton.setButtonText("Open output file");
    addAndMakeVisible(toggleOpenOutputButton);
    toggleOpenOutputButton.onClick = [this]()
    {
        m_OpenFileFlag = !m_OpenFileFlag;
    };

    // 
    inputFileButton.setButtonText("Select input file");
    addAndMakeVisible(inputFileButton);
    inputFileButton.onClick = [this]()
    {
        SelectInputFile();
    };

    //
    outputFileButton.setButtonText("Select output file");
    addAndMakeVisible(outputFileButton);
    outputFileButton.onClick = [this]()
    {
        SelectOutputFile();
    };
    
    //
    saveButton.setButtonText("Save");
    addAndMakeVisible(saveButton);
    saveButton.onClick = [this]()
    {
        Save();
    };
    saveButton.setEnabled(false);
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
            saveButton.setEnabled(!m_InputFilePath.empty() && !m_OutputFilePath.empty());
            if (!m_InputFilePath.empty())
            {
                Read();
            }
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
            saveButton.setEnabled(!m_InputFilePath.empty() && !m_OutputFilePath.empty());
        }
    );
}

void MainComponent::Read()
{
    m_pTableModel->Clear();
    if (!m_SceneParser->ReadJson(aze::g_ConverterUtf8Utf16.from_bytes(m_InputFilePath)))
    {
        juce::MessageBoxOptions mbo{};
        mbo.withMessage("Input file does not exist");
        NativeMessageBox::showAsync(mbo, [](int) {});
        m_InputFilePath.clear();
        saveButton.setEnabled(false);
        return;
    }
    else
    {
        for (auto& block : m_SceneParser->GetBlocks())
        {
            NamedVector3 nv3{};
            nv3.name = aze::g_ConverterUtf8Utf16.to_bytes(block.type);
            nv3.x = static_cast<float>(block.pos.x);
            nv3.y = static_cast<float>(block.pos.y);
            nv3.z = static_cast<float>(block.pos.z);
            m_pTableModel->AddNamedVectorData(nv3);
        }
    }
    m_DataTable.updateContent();
}

void MainComponent::Save()
{
    if (!m_SceneParser->WriteObj(aze::g_ConverterUtf8Utf16.from_bytes(m_OutputFilePath)))
    {
        juce::MessageBoxOptions mbo{};
        mbo.withMessage("Output file does not exist");
        NativeMessageBox::showAsync(mbo, [](int) {});
        m_OutputFilePath.clear();
        saveButton.setEnabled(false);
        return;
    }
    if (m_OpenFileFlag)
    {
        ShellExecute(NULL, "open", "explorer.exe", m_OutputFilePath.c_str(), NULL, SW_SHOWDEFAULT);
    }
}

void MainComponent::resized()
{
    m_DataTable.setBounds(200, 0, getWidth(), getHeight());
    inputFileButton.setBounds(10,10,150,30);
    outputFileButton.setBounds(10, 50, 150, 30);
    saveButton.setBounds(10, 90, 50, 30);
    toggleOpenOutputButton.setBounds(10, 130, 100, 30);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}


