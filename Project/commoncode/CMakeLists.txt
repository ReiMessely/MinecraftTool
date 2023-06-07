# Common code
add_library(CommonCode "Block.h" "Vector3.h" "SceneParser.h" "SceneParser.cpp" "Utils.h")

Set(CommonCodeIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)