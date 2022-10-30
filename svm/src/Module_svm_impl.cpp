#include <cstring>
#include "Module_svm_impl.h"
#include "debug.h"

CModule_svm_impl::CModule_svm_impl()
{

}
CModule_svm_impl::~CModule_svm_impl() 
{
#ifdef AI_ALG_DEBUG
    ALG_PRINT("%d,%s\n", __LINE__, __FUNCTION__);
#endif
}

void CModule_svm_impl::init()
{
    engine_init();
}

void CModule_svm_impl::svm_train(const float* train_data, const float* labels_data, const int num_data,
                                 const SVMConfig &config)
{
    config_ = config;
    engine_train(train_data, labels_data, num_data);
}

void CModule_svm_impl::svm_predict(const float* test_data, const int num_data)
{
    num_ = num_data;
    if(predicts_.size() < num_data)
    {
        predicts_.resize(num_data);
    }
    engine_predict(test_data, num_data, predicts_.data());
}

const float* CModule_svm_impl::get_result(size_t& num) const
{
    num = num_;
    return predicts_.data();
}
