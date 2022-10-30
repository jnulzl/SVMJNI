#include "Module_svm_opencv_impl.h"
#include "debug.h"

CModule_svm_opencv_impl::CModule_svm_opencv_impl()
{

}

CModule_svm_opencv_impl::~CModule_svm_opencv_impl()
{
#ifdef AI_ALG_DEBUG
    ALG_PRINT("%d,%s\n", __LINE__, __FUNCTION__);
#endif
}

void CModule_svm_opencv_impl::engine_init()
{
    svm_ = cv::ml::SVM::create();
}

void CModule_svm_opencv_impl::engine_train(const float* train_data, const float* labels_data, int num_data)
{
    svm_->setCoef0( config_.coef0 );
    svm_->setDegree( config_.degree );
    svm_->setGamma( config_.gamma );
    svm_->setKernel( config_.kernelType);
    svm_->setNu( config_.nu);
    svm_->setP( config_.p );
    svm_->setC( config_.c );
    svm_->setType( config_.type );

    cv::Mat XMat(num_data, config_.dim, CV_32FC1, const_cast<float*>(train_data));
    cv::Mat YMat(num_data, 1, CV_32FC1, const_cast<float*>(labels_data));
    svm_->train( XMat, cv::ml::ROW_SAMPLE, YMat );
}

void CModule_svm_opencv_impl::engine_predict(const float* test_data, int num_data, float* predict)
{
    for(int idx = 0; idx < num_data; ++idx)
    {
        cv::Mat sampleMat(1, config_.dim, CV_32FC1, const_cast<float*>(test_data + idx * config_.dim));
        predict[idx] = svm_->predict(sampleMat);
    }
}