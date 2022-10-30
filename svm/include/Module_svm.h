#ifndef MODULE_SVM_H
#define MODULE_SVM_H

#include "data_type.h"

class ALG_PUBLIC CModule_svm
{
public:
	CModule_svm();
	~CModule_svm();

    void init();

    void svm_train(const float* train_data, const float* labels_data, int num_data, const SVMConfig &config) const;

    void svm_predict(const float* test_data, int num_data) const;

    const float* get_result(size_t& num) const;

    void release();
private:
	AW_ANY_POINTER impl_;
};

#endif // MODULE_SVM_H

