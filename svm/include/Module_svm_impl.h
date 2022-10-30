#ifndef MODULE_SVM_IMPL_H
#define MODULE_SVM_IMPL_H

#include <string>
#include <vector>

#include "data_type.h"

class CModule_svm_impl
{
public:
	CModule_svm_impl();
	virtual ~CModule_svm_impl() ;

    void init();

	void svm_train(const float* train_data, const float* labels_data, int num_data, const SVMConfig &config);

    void svm_predict(const float* test_data, int num_data);

	const float* get_result(size_t& num) const;

protected:
    virtual void engine_init() = 0;
    virtual void engine_train(const float* train_data, const float* labels_data, int num_data) = 0;
    virtual void engine_predict(const float* test_data, int num_data, float* predict) = 0;

protected:
    SVMConfig config_;
    std::vector<float> predicts_;
    size_t num_;
};

#endif // MODULE_SVM_IMPL_H