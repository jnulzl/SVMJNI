# set(demo_src demo.cpp)
set(demo_src demo_c.cpp)
get_filename_component(exe_name ${demo_src} NAME_WLE)

add_executable(${exe_name} ${demo_src})
target_include_directories(${exe_name} PRIVATE
        ${PROJECT_SOURCE_DIR}/svm/include)

target_compile_options(${exe_name} PRIVATE
        -DPROJECT_ROOT="${PROJECT_SOURCE_DIR}"
        )

target_compile_definitions(${exe_name} PRIVATE
        $<$<BOOL:${USE_${ENGINE_UPPER}}>:USE_${ENGINE_UPPER}>
        )
if("Windows" STREQUAL ${CMAKE_SYSTEM_NAME})
    target_compile_definitions(${exe_name} PRIVATE
            USING_ALG_DLL
            )
endif()

if(NOT MSVC EQUAL ${CMAKE_CXX_COMPILER_ID})
    target_link_options(${exe_name} PRIVATE
            -Wl,--no-undefined
            -Wl,--no-allow-shlib-undefined
            )
    if(NOT("Windows" STREQUAL ${CMAKE_SYSTEM_NAME}))
        target_link_options(${exe_name} PRIVATE
#                -Wl,--enable-new-dtags # using RUNPATH (default)
                -Wl,--disable-new-dtags # using RPATH (default)
                )
    endif()
endif()

if(BUILD_SHARED_LIBS)
    target_link_libraries(${exe_name} PRIVATE
            ${LIB_NAME}
            )
else()
    if(MSVC EQUAL ${CMAKE_CXX_COMPILER_ID})
        target_link_libraries(${exe_name} PRIVATE
                ${LIB_NAME}
            )
    else()
        target_link_libraries(${exe_name} PRIVATE
            -Wl,--whole-archive ${LIB_NAME} -Wl,--no-whole-archive
        )
        target_link_options(${exe_name} PRIVATE
            -Wl,--allow-multiple-definition
        )
    endif()
endif()

if(NOT("Windows" STREQUAL ${CMAKE_SYSTEM_NAME}))
    target_link_libraries(${exe_name} PRIVATE
            m
            )
endif()
