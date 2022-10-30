cmake_minimum_required(VERSION 3.15)
project(SVMSVR)

set(CMAKE_SYSTEM_NAME "Linux") # Linux Android Windows

message(STATUS "Operate System : " ${CMAKE_SYSTEM_NAME})
message(STATUS "Compiler ID : " ${CMAKE_CXX_COMPILER_ID})
message(STATUS "Compiler Version : " ${CMAKE_CXX_COMPILER_VERSION})

# Select Engine
if(NOT ENGINE_LOWER)
    set(ENGINE_LOWER opencv) # mindsporelite mnn ncnn onnx paddlelite  tflite tflitegpu caffe openvino tensorrt tnn snpe
endif()
string(TOUPPER ${ENGINE_LOWER} ENGINE_UPPER)
set(USE_${ENGINE_UPPER} ON)
message(STATUS "Engine type is : " ${ENGINE_LOWER})

option(BUILD_SHARED_LIBS "If build shared library" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME})

string(TOLOWER ${CMAKE_SYSTEM_NAME} SYSTEM_LOWER)
include(${PROJECT_SOURCE_DIR}/cmake/${SYSTEM_LOWER}.cmake)

file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})
set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${EXECUTABLE_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${EXECUTABLE_OUTPUT_PATH})
set(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

set(INCLUDE_PATH ${INCLUDE_PATH}
        ${PROJECT_SOURCE_DIR}/common
        ${JAVA_INCLUDE}
        ${OpenCV_INCLUDE})

set(LIB_PATH ${LIB_PATH}
        ${OpenCV_LIB_PATH})

include_directories(${INCLUDE_PATH})
link_directories(${LIB_PATH})

add_subdirectory(svm)
add_subdirectory(examples)
