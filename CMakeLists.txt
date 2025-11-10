cmake_minimum_required (VERSION 3.14)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("txtpp")

include_directories(library)
add_library(txtpp STATIC
    src/simple_rule.cpp
 "chapter/2/tokenisation_example.cpp")
target_include_directories(txtpp PUBLIC "${PROJECT_SOURCE_DIR}/library")

add_subdirectory(chapter)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET txtpp PROPERTY CXX_STANDARD 20)
endif()