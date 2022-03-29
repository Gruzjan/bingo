cmake_minimum_required (VERSION 3.11)

add_subdirectory(third_party)

project(lysy-bingo
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(lysy-bingo
  src/main.cpp
)

target_include_directories(lysy-bingo PRIVATE src)
target_link_libraries(lysy-bingo PRIVATE smk)

set_target_properties(lysy-bingo PROPERTIES CXX_STANDARD 11)

target_compile_options(lysy-bingo PRIVATE -Wall -Wextra -pedantic -Werror)

# Detect emscripten is used.
if(EMSCRIPTEN)

  set_property(TARGET lysy-bingo APPEND_STRING PROPERTY LINK_FLAGS  " -s WASM=1")

  # Copy the index.html file.
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/index.html
    ${CMAKE_CURRENT_BINARY_DIR}/index.html
    COPYONLY
  )
  file(GLOB_RECURSE files "./resources/**")
  foreach(file ${files})
    file(RELATIVE_PATH relative_file ${CMAKE_SOURCE_DIR} "${file}")
    set_property(TARGET lysy-bingo APPEND_STRING PROPERTY LINK_FLAGS " --preload-file \"${file}@/${relative_file}\"")
    MESSAGE(STATUS " --preload-file \"${file}@/${relative_file}\"")
  endforeach()

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/style.css
    ${CMAKE_CURRENT_BINARY_DIR}/style.css
  )

endif()

install(TARGETS lysy-bingo RUNTIME DESTINATION "bin")
