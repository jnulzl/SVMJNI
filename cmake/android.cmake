set(CMAKE_SKIP_RPATH ON)
set(BUILD_SHARED_LIBS ON)

set(ANDROID_NDK_ABI_NAME "arm64-v8a") # armeabi-v7a arm64-v8a
set(OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${ANDROID_NDK_ABI_NAME})

set(ANDROID_THIRD /mnt/d/code/AndroidStudioProjects/third_party)
if("arm64-v8a" STREQUAL ${ANDROID_NDK_ABI_NAME})
    set(CMAKE_CXX_COMPILER /home/jnulzl/softwares/android-ndk-r23/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android21-clang++)
    set(CMAKE_C_COMPILER /home/jnulzl/softwares/android-ndk-r23/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android21-clang)
elseif("armeabi-v7a" STREQUAL ${ANDROID_NDK_ABI_NAME})
    set(CMAKE_CXX_COMPILER /home/jnulzl/softwares/android-ndk-r23/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi21-clang++)
    set(CMAKE_C_COMPILER /home/jnulzl/softwares/android-ndk-r23/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi21-clang)
endif()

##############OpenCV##############
set(OpenCV_DIR "${ANDROID_THIRD}/opencv-4.1.1-android-sdk/sdk/native/jni")
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OpenCV library status:")
    message(STATUS "    version: ${OpenCV_VERSION}")
    message(STATUS "    libraries: ${OpenCV_LIBS}")
    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
else(OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found")
endif(OpenCV_FOUND)

set(OpenCV_INCLUDE ${OpenCV_INCLUDE_DIRS})
set(OpenCV_LIB_PATH
        ${OpenCV_DIR}/../staticlibs/${ANDROID_NDK_ABI_NAME}
        ${OpenCV_DIR}/../3rdparty/libs/${ANDROID_NDK_ABI_NAME}
        )
set(OpenCV_VERSION "")