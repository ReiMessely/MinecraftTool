file(GLOB Headers "*.h")

add_library(headeronlylib INTERFACE ${Headers})

Set(HeaderOnlyLib "${CMAKE_CURRENT_SOURCE_DIR}" PARENT_SCOPE)