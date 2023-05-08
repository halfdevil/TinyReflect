# CMakeList.txt : CMake project for TinyReflect-HeaderTool, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

project ("TinyReflect-HeaderTool")

find_package(LLVM REQUIRED CONFIG)
list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})

include(ChooseMSVCCRT)
include(AddLLVM)
include(HandleLLVMOptions)

find_package(Clang REQUIRED)

file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c??)

add_executable("TinyReflect-HeaderTool" ${SOURCE_FILES} ${HEADER_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET "TinyReflect-HeaderTool" PROPERTY CXX_STANDARD 20)
endif()

set(INCLUDE_DIRS ${LLVM_INCLUDE_DIR} ${CLANG_INCLUDE_DIRS} "Include")
set(COMPILE_DEFS ${LLVM_DEFINITIONS})
set(LINK_DIRS ${LLVM_LIBRARY_DIR})
set(LINK_LIBRARIES "TinyReflect-Framework" "clangTooling" "clangBasic" 
	"clangASTMatchers" "clangFrontend")

if (CMAKE_BUILD_TYPE MATCHES Debug)
	set(COMPILE_DEFS ${COMPILE_DEFS} DEBUG_BUILD=1)  
endif()

if (MSVC)
	set(COMPILE_DEFS ${COMPILE_DEFS} -D_CONSOLE)
endif()

target_include_directories("TinyReflect-HeaderTool" PUBLIC ${INCLUDE_DIRS})
target_compile_definitions("TinyReflect-HeaderTool" PUBLIC ${COMPILE_DEFS})
target_link_directories("TinyReflect-HeaderTool" PRIVATE ${LINK_DIRS})
target_link_libraries("TinyReflect-HeaderTool" PUBLIC ${LINK_LIBRARIES})
