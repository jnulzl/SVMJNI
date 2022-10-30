//
// Created by lizhaoliang-os on 2022/10/25.
//
#ifndef SVMSVR_MODULE_SVM_C_API_H
#define SVMSVR_MODULE_SVM_C_API_H

#include "data_type.h"

#ifdef __cplusplus
extern "C" {
#endif

void ALG_PUBLIC alg_svm_init(Handle* handle);

void ALG_PUBLIC alg_svm_release(Handle handle);

void ALG_PUBLIC alg_svm_train(Handle handle, const float* train_data,
                              const float* labels_data, int num_data,
                              const SVMConfig &config);

void ALG_PUBLIC alg_svm_predict(Handle handle, const float* test_data, int num_data);

void ALG_PUBLIC alg_svm_get_result(Handle handle, const float** pred, size_t& num_data);

#ifdef __cplusplus
}
#endif

#endif // SVMSVR_MODULE_SVM_C_API_H
