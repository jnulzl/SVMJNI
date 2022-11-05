cmake_minimum_required(VERSION 3.15)
project(SVMJNI)
if(NOT SYSTEM_NAME)
    set(SYSTEM_NAME "Linux") # Linux Android Windows
endif()
set(CMAKE_SYSTEM_NAME ${SYSTEM_NAME})
message(STATUS "System name is : " ${CMAKE_SYSTEM_NAME})

string(TOLOWER ${PROJECT_NAME} LIB_NAME)

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


# Install lib
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
message(STATUS "Install root directory is : " ${CMAKE_INSTALL_PREFIX})
message(STATUS "Build       type       is : " ${CMAKE_BUILD_TYPE})
##############Install lib##############
install(TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION lib
        )
##############Install include##############
set(include_pub_all
        ${include_pub_all}
        ${CMAKE_CURRENT_SOURCE_DIR}/common/data_type.h
        )
install(FILES ${include_pub_all} DESTINATION include)
set(example_pub_all
        ${example_pub_all}
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/demo_c.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/SVMJNI.java
        )
install(FILES ${example_pub_all} DESTINATION demo)
