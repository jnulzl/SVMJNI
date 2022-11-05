//
// Created by lizhaoliang-os on 2020/6/23.
//

#ifndef ALG_DEFINE_H
#define ALG_DEFINE_H

#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>

#if defined(__ANDROID__)
    #include <android/log.h>
    #define ALG_ERROR(format, ...) __android_log_print(ANDROID_LOG_ERROR, "ALGJNI", format, ##__VA_ARGS__)
    #define ALG_PRINT(format, ...) __android_log_print(ANDROID_LOG_INFO, "ALGJNI", format, ##__VA_ARGS__)
#else
    #define ALG_PRINT(format, ...) printf("%d, %s:", __LINE__, __FUNCTION__); \
                                        printf(format, ##__VA_ARGS__)
    #define ALG_ERROR(format, ...) printf("%d, %s:", __LINE__, __FUNCTION__); \
                                        printf(format, ##__VA_ARGS__)
#endif

#ifdef DEBUG
#define ALG_ASSERT(x)                                            \
    {                                                            \
        int res = (x);                                           \
        if (!res) {                                              \
            ALG_ERROR("Error for %s, %d\n", __FILE__, __LINE__); \
            assert(res);                                         \
        }                                                        \
    }
#else
#define ALG_ASSERT(x)                                            \
    {                                                            \
        int res = (x);                                           \
        if (!res) {                                              \
            ALG_ERROR("Error for %d\n", __LINE__); \
        }                                                        \
    }
#endif


#define ANY_POINTER_CAST(impl, T) reinterpret_cast<T*>(impl)

#define ALG_ENGINE_IMPL(alg, lower_name)  \
    CModule_##alg##_##lower_name##_impl()

#endif //ALG_DEFINE_H
