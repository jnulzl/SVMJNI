#include "Module_svm_opencv_impl.h"
#include "Module_svm.h"
#include "alg_define.h"

CModule_svm::CModule_svm()
{
    impl_ = new ALG_ENGINE_IMPL(svm, opencv);
}