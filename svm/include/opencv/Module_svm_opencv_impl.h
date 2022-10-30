//
// Created by lizhaoliang-os on 2020/6/9.
//

#ifndef MODULE_SVM_OPENCV_IMPL_H
#define MODULE_SVM_OPENCV_IMPL_H

#include <memory>

#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>

#include "Module_svm_impl.h"


class CModule_svm_opencv_impl : public CModule_svm_impl
{
public:
    CModule_svm_opencv_impl();
    virtual ~CModule_svm_opencv_impl();

private:
    virtual void engine_init() override;
    virtual void engine_train(const float* train_data, const float* labels_data, int num_data) override;
    virtual void engine_predict(const float* test_data, int num_data, float* predict) override;

private:
    cv::Ptr<cv::ml::SVM> svm_;
};

#endif //MODULE_YOLOV5_MNN_IMPL_H
