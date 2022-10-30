/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class SVMJNI */

#ifndef _Included_SVMJNI
#define _Included_SVMJNI

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     SVMJNI
 * Method:    svmInit
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_SVMJNI_svmInit(JNIEnv* env, jobject self);

/*
 * Class:     SVMJNI
 * Method:    svmTrain
 * Signature: (J[F[FIIDDDDDDI)V
 */
JNIEXPORT void JNICALL Java_SVMJNI_svmTrain(JNIEnv* env , jobject self, jlong handle, jfloatArray trainData, jfloatArray trainLabel,
                                            jint dim, jint type, jdouble gamma, jdouble coef0, jdouble degree,
                                            jdouble c, jdouble nu, jdouble p, jint kernelType);

/*
 * Class:     SVMJNI
 * Method:    svmPredict
 * Signature: (J[FI)[F
 */
JNIEXPORT jfloatArray JNICALL Java_SVMJNI_svmPredict(JNIEnv* env, jobject self, jlong handle, jfloatArray testData, jint dim);

/*
 * Class:     SVMJNI
 * Method:    svmRelease
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_SVMJNI_svmRelease(JNIEnv* env, jobject self,jlong handle);

#ifdef __cplusplus
}
#endif

#endif
