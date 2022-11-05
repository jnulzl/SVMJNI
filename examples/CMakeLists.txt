# set(demo_src demo.cpp)
set(demo_src demo_c.cpp)
get_filename_component(exe_name ${demo_src} NAME_WLE)

add_executable(${exe_name} ${demo_src})
target_include_directories(${exe_name} PRIVATE
        ${PROJECT_SOURCE_DIR}/svm/include)

target_compile_definitions(${exe_name} PRIVATE
        $<$<BOOL:${USE_${ENGINE_UPPER}}>:USE_${ENGINE_UPPER}>
        )

target_link_options(${exe_name} PRIVATE
        -Wl,--no-undefined
        -Wl,--no-allow-shlib-undefined
        )

target_link_libraries(${exe_name} PRIVATE
        ${LIB_NAME}
        m
        )