if(NOT OpenCV_DIR)
    set(OpenCV_DIR "/usr/")
endif()
message(STATUS "OpenCV_DIR :  " ${OpenCV_DIR})
##############OpenCV##############
set(OpenCV_INCLUDE
        ${OpenCV_DIR}/include/
        ${OpenCV_DIR}/include/opencv2
        ${OpenCV_DIR}/include/opencv4
        ${OpenCV_DIR}/include/opencv4/opencv2)
set(OpenCV_LIB_PATH
        ${OpenCV_DIR}/lib/x86_64-linux-gnu
        ${OpenCV_DIR}/lib/)

if(NOT JAVA_HOME)
    set(JAVA_HOME "/usr/lib/jvm/java-8-openjdk-amd64")
endif()
set(JAVA_INCLUDE
        ${JAVA_HOME}/include/
        ${JAVA_HOME}/include/linux)