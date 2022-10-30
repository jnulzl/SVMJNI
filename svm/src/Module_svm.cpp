#include "Module_svm_impl.h"
#include "Module_svm.h"
#include "Module_svm_c_api.h"

#include "alg_define.h"
#include "debug.h"

CModule_svm::~CModule_svm()
{
    if(impl_)
    {
        delete ANY_POINTER_CAST(impl_, CModule_svm_impl);
        impl_ = nullptr;
#ifdef AI_ALG_DEBUG
        ALG_PRINT("%d,%s\n", __LINE__, __FUNCTION__);
#endif
    }
}

void CModule_svm::init()
{
    ANY_POINTER_CAST(impl_, CModule_svm_impl)->init();
}

void CModule_svm::svm_train(const float* train_data, const float* labels_data, const int num_data, const SVMConfig &config) const
{
    ANY_POINTER_CAST(impl_, CModule_svm_impl)->svm_train(train_data, labels_data, num_data, config);
}

void CModule_svm::svm_predict(const float *test_data, const int num_data) const
{
    ANY_POINTER_CAST(impl_, CModule_svm_impl)->svm_predict(test_data, num_data);
}

const float* CModule_svm::get_result(size_t& num) const
{
    return ANY_POINTER_CAST(impl_, CModule_svm_impl)->get_result(num);
}

void CModule_svm::release()
{
    if(impl_)
    {
        delete ANY_POINTER_CAST(impl_, CModule_svm_impl);
        impl_ = nullptr;
#if defined(ALG_DEBUG) || defined(AI_ALG_DEBUG)
        std::printf("%d,%s\n", __LINE__, __FUNCTION__);
#endif
    }
}


/************************* c api *************************/
void alg_svm_init(Handle* handle)
{
    *handle = new CModule_svm();
    ANY_POINTER_CAST(*handle, CModule_svm)->init();
}

void alg_svm_release(Handle handle)
{
    if(handle)
    {
        ANY_POINTER_CAST(handle, CModule_svm)->release();
        delete ANY_POINTER_CAST(handle, CModule_svm);
    }
}

void alg_svm_train(Handle handle, const float* train_data, const float* labels_data, int num_data,
                   const SVMConfig &config)
{
    ANY_POINTER_CAST(handle, CModule_svm)->svm_train(train_data, labels_data, num_data, config);
}

void alg_svm_predict(Handle handle, const float* test_data, int num_data)
{
    ANY_POINTER_CAST(handle, CModule_svm)->svm_predict(test_data, num_data);
}

void alg_svm_get_result(Handle handle, const float** pred, size_t& num_data)
{
    *pred = ANY_POINTER_CAST(handle, CModule_svm)->get_result(num_data);
}