# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project("TinyReflect-Sample")

file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c??)
file(GLOB_RECURSE GENERATED_HEADER_FILES "${CMAKE_CURRENT_BINARY_DIR}/Generated/*.h")
file(GLOB_RECURSE GENERATED_SOURCE_FILES "${CMAKE_CURRENT_BINARY_DIR}/Generated/*.c??")

add_executable("TinyReflect-Sample" ${SOURCE_FILES} ${HEADER_FILES}
	${GENERATED_HEADER_FILES} ${GENERATED_SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET "TinyReflect-Sample" PROPERTY CXX_STANDARD 20)
endif()

set(INCLUDE_DIRS "Include")
set(LINK_OPTIONS "")
set(LINK_LIBRARIES "TinyReflect-Framework")

if (CMAKE_BUILD_TYPE MATCHES Debug)
	set(COMPILE_DEFS ${COMPILE_DEFS} DEBUG_BUILD=1)  
endif()

if (MSVC)
	set(COMPILE_DEFS ${COMPILE_DEFS} -D_CONSOLE)
endif()

target_include_directories("TinyReflect-Sample" PUBLIC ${INCLUDE_DIRS})
target_compile_definitions("TinyReflect-Sample" PUBLIC ${COMPILE_DEFS})
target_link_libraries("TinyReflect-Sample" PUBLIC ${LINK_LIBRARIES} ${LINK_OPTIONS})
