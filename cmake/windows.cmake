if(NOT OpenCV_DIR)
#    set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/third_party/Windows/OpenCV-MinGW-Build-OpenCV-4.5.2-x64)
set(OpenCV_DIR E:/softwares/opencv-4.3.0-dldt-2020.2-vc16-avx2/opencv/build_release)
endif()
set(OpenCV_VERSION 430)
message(STATUS "OpenCV_DIR :  " ${OpenCV_DIR})
##############OpenCV##############
set(OpenCV_INCLUDE
        ${OpenCV_DIR}/include/
        ${OpenCV_DIR}/include/opencv2
        ${OpenCV_DIR}/include/opencv4
        ${OpenCV_DIR}/include/opencv4/opencv2)
set(OpenCV_LIB_PATH
        ${OpenCV_DIR}/lib/x86_64-linux-gnu
        ${OpenCV_DIR}/x64/mingw/lib/
        ${OpenCV_DIR}/lib/)

if(NOT JAVA_HOME)
    set(JAVA_HOME "D:/ProgramData/jdk-11.0.2")
endif()
set(JAVA_INCLUDE
        ${JAVA_HOME}/include/
        ${JAVA_HOME}/include/win32)