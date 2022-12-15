cmake_minimum_required(VERSION 3.21)
project(test VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

set(GLYPHS glyphs)

add_executable(glyph ${GLYPHS}.c)
target_compile_options(glyph PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address,undefined)
target_link_options(glyph PRIVATE -fsanitize=address,undefined)
target_compile_definitions(glyph PRIVATE -DGLYPH_WIDTH=7 -DGLYPH_HEIGHT=7 -DGLYPH_SPACING=1)

set_target_properties(glyph 
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)