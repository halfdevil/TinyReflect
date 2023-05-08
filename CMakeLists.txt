# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("TinyReflect")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(GLOBAL PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory("ThirdParty/json")
set_property(TARGET nlohmann_json PROPERTY FOLDER "ThirdParty")
include_directories("ThirdParty/json/include")

add_subdirectory("Framework")
add_subdirectory("HeaderTool")
add_subdirectory("Samples")
