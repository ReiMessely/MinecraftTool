# Set the source files for the project
set(SOURCES
    Main.cpp
    MainComponent.h
    MainComponent.cpp
)

# Add an executable target for the project
juce_add_gui_app(MinecraftToolGUI
    PRODUCT_NAME "Minecraft tool"
    VERSION ${PROJECT_VERSION}
    COMPANY_NAME "Wardergrip"
    DOCUMENT_EXTENSIONS "grip"
    DOCUMENT_NAMES "My Document"
    DOCUMENT_DESCRIPTIONS "Minecrafttool to convert json to voxel based scenes in obj"
)

juce_generate_juce_header(MinecraftToolGUI)

target_sources(MinecraftToolGUI PRIVATE ${SOURCES} "TableModel.h" "TableModel.cpp" "NamedVector3.h" "NamedVector3.cpp")

# Link against the JUCE module
target_link_libraries(MinecraftToolGUI
    PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_include_directories(
	MinecraftToolGUI PUBLIC 
	"${CommonCodeIncludeDir}"
)
target_link_libraries(
	MinecraftToolGUI PUBLIC CommonCode
)
