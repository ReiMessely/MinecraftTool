cmake_minimum_required(VERSION 3.22)

project(MinecraftTool)

add_subdirectory(headeronlylib)
message("Include directory: ${HeaderOnlyIncludeDir}")


add_subdirectory(commoncode)
message("Include directory: ${CommonCodeIncludeDir}")

# Adding the subdirectory builds your GUI tool seperately
add_subdirectory(gui)
message("Include directory: ${GuiIncludeDirectory}")

add_subdirectory(consoletool)

target_include_directories(
    consoletool PUBLIC
    "${CommonCodeIncludeDir}"
    "${HeaderOnlyLibIncludeDir}"
)

target_link_libraries( consoletool PUBLIC CommonCode)