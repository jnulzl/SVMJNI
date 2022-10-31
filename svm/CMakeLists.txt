file(GLOB _tmp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(src_all ${src_all} ${_tmp})
file(GLOB _tmp ${CMAKE_CURRENT_SOURCE_DIR}/src/${ENGINE_LOWER}/*.cpp)
set(src_all ${src_all} ${_tmp})

# For jni
file(GLOB _tmp ${CMAKE_CURRENT_SOURCE_DIR}/jni/*.cpp)
set(src_all ${src_all} ${_tmp})
set(include_all ${include_all}
        ${CMAKE_CURRENT_SOURCE_DIR}/jni
        )

file(GLOB _tmp ${PROJECT_SOURCE_DIR}/common/*.cpp)
set(src_all ${src_all} ${_tmp})
set(include_all ${include_all}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

set(include_pub_all ${include_pub_all}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Module_svm.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Module_svm_c_api.h
        PARENT_SCOPE
        )

if (BUILD_SHARED_LIBS)
    add_library(${LIB_NAME} SHARED ${src_all})
else()
    add_library(${LIB_NAME} STATIC ${src_all})
endif ()

target_include_directories(${LIB_NAME} PRIVATE
        ${include_all}
        $<$<BOOL:${USE_${ENGINE_UPPER}}>:${CMAKE_CURRENT_SOURCE_DIR}/include/${ENGINE_LOWER}>
        )

target_compile_definitions(${LIB_NAME} PRIVATE
        $<$<BOOL:${USE_${ENGINE_UPPER}}>:USE_${ENGINE_UPPER}>
        )

if(NOT MSVC EQUAL ${CMAKE_CXX_COMPILER_ID})
    set_target_properties(${LIB_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)
    target_compile_options(${LIB_NAME} PRIVATE
            -fvisibility=hidden -fvisibility-inlines-hidden
            )

    if("Rpi" STREQUAL ${CMAKE_SYSTEM_NAME})
        target_link_options(${LIB_NAME} PRIVATE
                -Wl,--warn-unresolved-symbols
                )
    else()
        target_link_options(${LIB_NAME} PRIVATE
                -Wl,--no-undefined
                -Wl,--no-allow-shlib-undefined
                )
    endif()
endif()

if("Windows" STREQUAL ${CMAKE_SYSTEM_NAME})
    target_compile_definitions(${LIB_NAME} PRIVATE
            BUILDING_ALG_DLL
            )
    target_link_libraries(${LIB_NAME} PRIVATE
            opencv_core${OpenCV_VERSION}
            opencv_ml${OpenCV_VERSION}
            )
else()
    target_link_libraries(${LIB_NAME} PRIVATE
            -Wl,--whole-archive libopencv_core.a -Wl,--no-whole-archive
            -Wl,--whole-archive libopencv_ml.a -Wl,--no-whole-archive
            dl
            z
            )
    if("Android" STREQUAL ${CMAKE_SYSTEM_NAME})
        target_link_libraries(${LIB_NAME} PUBLIC
                log
                -Wl,--whole-archive libtbb.a -Wl,--no-whole-archive
                -Wl,--whole-archive libtegra_hal.a -Wl,--no-whole-archive
                -Wl,--whole-archive libittnotify.a -Wl,--no-whole-archive
                )
    else()
        target_link_libraries(${LIB_NAME} PRIVATE
                pthread
                tbb
                )
    endif()
endif()


