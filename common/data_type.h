//
// Created by jnulzl on 2020/5/24.
//

#ifndef AI_ALG_DATA_TYPE_H
#define AI_ALG_DATA_TYPE_H

#if defined(_MSC_VER) || defined(WIN32)
    #if defined(BUILDING_ALG_DLL)
        #define ALG_PUBLIC __declspec(dllexport)
    #elif defined(USING_ALG_DLL)
        #define ALG_PUBLIC __declspec(dllimport)
    #else
        #define ALG_PUBLIC
    #endif
#else
    #define ALG_PUBLIC __attribute__((visibility("default")))
#endif

typedef void* AW_ANY_POINTER;
typedef void* Handle;

struct SVMConfig {
    /** Type of a SVM formulation.*/
    int type = 103; // C_SVC = 100, NU_SVC = 101, ONE_CLASS=102, EPS_SVR=103, NU_SVR=104

    /** Parameter gamma of a kernel function.*/
    double gamma = 1.0;

    /** Parameter _coef0_ of a kernel function.*/
    double coef0 = 0.0;

    /** Parameter _degree_ of a kernel function.*/
    double degree = 1.0;

    /** Parameter _C_ of a SVM optimization problem.*/
    double c = 1.0;

    /** Parameter nu of a SVM optimization problem.*/
    double nu = 0.0;

    /** Parameter epsilon of a SVM optimization problem.*/
    double p = 0.1;

    /** Type of a SVM kernel.*/
    int kernelType = 2; // LINEAR=0, POLY=1, RBF=2, SIGMOID=3, CHI2=4, INTER=5

    /** Dim of SVM train/test data.*/
    int dim = 1;
};

#define PI (3.141592653589793)

#endif //AI_ALG_DATA_TYPE_H
