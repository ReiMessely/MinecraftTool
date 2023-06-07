# Common code
add_library(CommonCode "Block.h" "Vector3.h" "Utils.h" "SceneParser.h" "SceneParser.cpp")

set(CommonCodeIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)

target_include_directories(
    CommonCode PUBLIC
    "${CommonCodeIncludeDir}"
    "${HeaderOnlyIncludeDir}"
)