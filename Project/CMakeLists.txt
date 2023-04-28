cmake_minimum_required(VERSION 3.22)

project(MinecraftTool)

add_subdirectory(headeronlylib)
message("Include directory: ${HeaderOnlyIncludeDir}")

#add_subdirectory(sceneparser)
#message("Include directory: ${SceneParserIncludeDir}")

add_subdirectory(commoncode)
message("Include directory: ${CommonCodeIncludeDir}")

add_subdirectory(consoletool)

target_include_directories(
    consoletool PUBLIC
    "${CommonCodeIncludeDir}"
    "${HeaderOnlyLibIncludeDir}"
    #"${SceneParserIncludeDir}"
)