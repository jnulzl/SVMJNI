//#include <pthread.h>
#include <mutex>
#include <jni.h>
#include "SVMJNI.h"
#include "Module_svm.h"

//pthread_mutex_t __awHumanEngine_mutex_ = PTHREAD_MUTEX_INITIALIZER;
static std::mutex io_mutex;
//static CModule_svm _static_svm;

/*
 * Class:     SVMJNI
 * Method:    svmInit
 * Signature: ()V
 */
JNIEXPORT jlong JNICALL Java_SVMJNI_svmInit(JNIEnv* env, jobject self)
{
    std::lock_guard<std::mutex> lk(io_mutex);
    CModule_svm* svm_ptr_ = new CModule_svm();
    svm_ptr_->init();
    return reinterpret_cast<jlong>(svm_ptr_);
}

/*
 * Class:     SVMJNI
 * Method:    svmTrain
 * Signature: ([F[FIIDDDDDDI)V
 */
JNIEXPORT void JNICALL Java_SVMJNI_svmTrain(JNIEnv* env , jobject self, jlong handle, jfloatArray trainData, jfloatArray trainLabel,
                                            jint dim, jint type, jdouble gamma, jdouble coef0, jdouble degree,
                                            jdouble c, jdouble nu, jdouble p, jint kernelType)
{
    std::lock_guard<std::mutex> lk(io_mutex);
    SVMConfig svmConfig;
    svmConfig.dim = dim; // train data dim
    svmConfig.type = type;
    svmConfig.gamma = gamma;
    svmConfig.coef0 = coef0;
    svmConfig.degree = degree;
    svmConfig.c = c;
    svmConfig.nu = nu;
    svmConfig.p = p;
    // LINEAR=0, POLY=1, RBF=2, SIGMOID=3, CHI2=4, INTER=5
    svmConfig.kernelType = kernelType;

    // Step 1: Convert the incoming JNI jfloatArray to C's jfloat[]
    jfloat *train_data = env->GetFloatArrayElements(trainData, nullptr);
    if (!train_data)
        return;
    jfloat *train_label = env->GetFloatArrayElements(trainLabel, nullptr);
    if (!train_label)
        return;
    jsize train_num = env->GetArrayLength(trainLabel);

    // Step 2: Perform its intended operations
    /** Train the SVM */
//    _static_svm.svm_train(train_data, train_label, train_num, svmConfig);
    reinterpret_cast<CModule_svm*>(handle)->svm_train(train_data, train_label, train_num, svmConfig);
    env->ReleaseFloatArrayElements(trainData, train_data, 0); // release resources
    env->ReleaseFloatArrayElements(trainLabel, train_label, 0); // release resources
}

/*
 * Class:     SVMJNI
 * Method:    svmPredict
 * Signature: ([F)[F
 */
JNIEXPORT jfloatArray JNICALL Java_SVMJNI_svmPredict(JNIEnv* env, jobject self, jlong handle, jfloatArray testData, jint dim)
{
    std::lock_guard<std::mutex> lk(io_mutex);
    // Step 1: Convert the incoming JNI jfloatArray to C's jfloat[]
    jfloat *test_data = env->GetFloatArrayElements(testData, nullptr);
    if (!test_data)
        return nullptr;
    jsize data_num = env->GetArrayLength(testData);
    jsize test_num = data_num / dim;
    // Step 2: Perform its intended operations
    /** Predict the SVM */
//    _static_svm.svm_predict(test_data, test_num);
    reinterpret_cast<CModule_svm*>(handle)->svm_predict(test_data, test_num);
    env->ReleaseFloatArrayElements(testData, test_data, 0); // release resources

    size_t num = 0;
//    const jfloat* pred = _static_svm.get_result(num);
    const jfloat* pred = reinterpret_cast<CModule_svm*>(handle)->get_result(num);

    // Step 3: Convert the C's Native jdouble[] to JNI jdoublearray, and return
    jfloatArray outJNIArray = env->NewFloatArray(static_cast<jsize>(num));  // allocate
    if (!outJNIArray)
        return nullptr;
    env->SetFloatArrayRegion(outJNIArray, 0 , static_cast<jsize>(num), pred);  // copy
    return outJNIArray;
}

/*
 * Class:     SVMJNI
 * Method:    svmRelease
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_SVMJNI_svmRelease(JNIEnv* env, jobject self, jlong handle)
{
    std::lock_guard<std::mutex> lk(io_mutex);
    //    _static_svm.release();
    reinterpret_cast<CModule_svm*>(handle)->release();
}
