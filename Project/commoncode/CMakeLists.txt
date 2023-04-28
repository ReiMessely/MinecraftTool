# Common code
add_library(CommonCode INTERFACE "Block.h" "Vector3.h")

Set(CommonCodeIncludeDir "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)