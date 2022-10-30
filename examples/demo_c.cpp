//
// Created by lizhaoliang-os on 2022/10/24.
//

#include <iostream>
#include <cmath>
#include <vector>
#include "Module_svm_c_api.h"

float funcLinear(float x)
{
    // Linear f(x) = 2x + 1       ---> kernelType = 0
    return 2 * x + 1;
}

float funcPoly(float x)
{
    // Ploy   f(x) = x^2 + 1 ---> kernelType = 1
    return 2 * x * x + 1;
}

float funcRBF(float x)
{
    // RBF    f(x) = sin(x) + 1    ---> kernelType = 2
    return std::sin(x) + 1;
}

float mse(const float* input, const float* predict, size_t len)
{
    float mse_val = 0;
    for (size_t idx = 0; idx < len; ++idx)
    {
        float diff = input[idx] - predict[idx];
        mse_val += (diff * diff);
    }
    mse_val /= len;
    return mse_val;
}

using FUNCPtr = float (*)(float);
float testSVR1D(const FUNCPtr& func_ptr, int kernelType, int train_num, int dim = 1)
{
    /** Set up training data */
    std::vector<float> X(train_num, 0);
    std::vector<float> Y(train_num, 0);
    for (int idx = 0; idx < train_num; ++idx)
    {
        X[idx] = idx;
        Y[idx] = func_ptr(X[idx]);
    }

    /** Set up svm config */
    SVMConfig svmConfig;
    svmConfig.dim = dim; // train data dim
    svmConfig.coef0 = 0.0;
    svmConfig.degree = 2.0;
    svmConfig.gamma = 1.0;
    svmConfig.p = 0.1;
    svmConfig.c = 1.0;

    // LINEAR=0, POLY=1, RBF=2, SIGMOID=3, CHI2=4, INTER=5
    svmConfig.kernelType = kernelType;

    /** Init svm */
    Handle handle;
    alg_svm_init(&handle);

    /** Train the SVM */
    alg_svm_train(handle, X.data(), Y.data(), train_num, svmConfig);

    /** Predict the SVM */
    alg_svm_predict(handle, X.data(), train_num);

    /** Get SVM predict */
    const float* pred = nullptr;
    size_t num = -1;
    alg_svm_get_result(handle, &pred, num);
    float mse_val = mse(Y.data(), pred, num);

    /** Print mse */
    alg_svm_release(handle);
    return mse_val;
}



float func2DLinear(float x, float y)
{
    // Linear f(x) = 2x + 2y + 1       ---> kernelType = 0
    return 2 * x + 2 * y + 1;
}

float func2DPoly(float x, float y)
{
    // Ploy   f(x) = 2x^2 + 2y^2 + 1 ---> kernelType = 1
    return 2 * x * x + 2 * y * y + 1;
}

float func2DRBF(float x, float y)
{
    // RBF    f(x) = sin(x) + cos(y) + 1    ---> kernelType = 2
    return std::sin(x) + std::cos(y) + 1;
}

using FUNC2DPtr = float (*)(float, float);
float testSVR2D(const FUNC2DPtr& func_ptr, int kernelType, int train_num, int dim = 2)
{
    /** Set up training data */
    std::vector<float> X(train_num * train_num * dim, 0);
    std::vector<float> Y(train_num * train_num, 0);
    for (int idx = 0; idx < train_num; ++idx)
    {
        for (int idy = 0; idy < train_num; ++idy)
        {
            X[idx * train_num * dim + dim * idy] = idx;
            X[idx * train_num * dim + dim * idy + 1] = idy;
            Y[idx * train_num + idy] = func_ptr(idx, idy);
        }
    }

    /** Set up svm config */
    SVMConfig svmConfig;
    svmConfig.dim = dim; // train data dim
    svmConfig.coef0 = 0.0;
    svmConfig.degree = 2.0;
    svmConfig.gamma = 1.0;
    svmConfig.p = 0.1;
    svmConfig.c = 1.0;

    // LINEAR=0, POLY=1, RBF=2, SIGMOID=3, CHI2=4, INTER=5
    svmConfig.kernelType = kernelType;

    /** Init svm */
    Handle handle;
    alg_svm_init(&handle);

    /** Train the SVM */
    alg_svm_train(handle, X.data(), Y.data(), Y.size(), svmConfig);

    /** Predict the SVM */
    alg_svm_predict(handle, X.data(), Y.size());

    /** Get SVM predict */
    const float* pred = nullptr;
    size_t num = -1;
    alg_svm_get_result(handle, &pred, num);
    float mse_val = mse(Y.data(), pred, num);

    /** Print mse */
    alg_svm_release(handle);
    return mse_val;
}

int main(int argc, const char* argv[])
{
    int train_num = 8;
    std::cout << "1D Linear regression mse: " << testSVR1D(funcLinear, 0, train_num) << std::endl;
    std::cout << "1D Poly   regression mse: " << testSVR1D(funcPoly, 1, train_num) << std::endl;
    std::cout << "1D RBF    regression mse: " << testSVR1D(funcRBF, 2, train_num) << std::endl;

    std::cout << "2D Linear regression mse: " << testSVR2D(func2DLinear, 0, train_num) << std::endl;
    std::cout << "2D Poly   regression mse: " << testSVR2D(func2DPoly, 1, train_num) << std::endl;
    std::cout << "2D RBF    regression mse: " << testSVR2D(func2DRBF, 2, train_num) << std::endl;
    return 0;
}
