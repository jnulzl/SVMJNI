import java.lang.Math;

public class SVMJNI
{  // Save as HelloJNI.java
   static
   {
      System.loadLibrary("svmjni"); // Load native library svmjni.dll (Windows) or libsvmjni.so (Unixes)
                                   //  at runtime
                                   // This library contains a native method called sayHello()
   }   

    /**
     * 初始化句柄
     * @return handle
     */
	private native long svmInit();

    /**
     * SVM训练接口
     * @param handle       // svmInit的返回值
     * @param trainData    // 训练数据，  例如二维数据(z = f(x,y))：x1,y1,x2,y2,x3,y3,x4,y4,......
     * @param trainLabel   // 训练数据对应的标签,例如：z1,z2,z3,z4,......
     * @param dim          // 训练数据维度， 例如,z = f(x,y),则dim=2
     * @param type         // Type of a SVM formulation,
                           // 可选值为：C_SVC = 100, NU_SVC = 101, ONE_CLASS=102, EPS_SVR=103, NU_SVR=104,
     * @param gamma        // Parameter gamma of a kernel function.
     * @param coef0        // Parameter _coef0_ of a kernel function.
     * @param degree       // Parameter _degree_ of a kernel function.
     * @param c            // Parameter _C_ of a SVM optimization problem.
     * @param nu           // Parameter nu of a SVM optimization problem.
     * @param p            // Parameter epsilon of a SVM optimization problem.
     * @param kernelType   // Type of a SVM kernel.
     */
	private native void svmTrain(long handle, float[] trainData, float[] trainLabel, int dim,
								int type, double gamma, double coef0, double degree,
								double c, double nu, double p, int kernelType);

    /**
     * SVM预测接口
     * @param handle      // svmInit的返回值
     * @param testData    // 测试数据，例如二维数据(z = f(x,y))：x1,y1,x2,y2,x3,y3,x4,y4,...... 维度必须与训练数据保持一致
     * @param dim         // 测试数据维度， 例如,z = f(x,y),则dim=2. 维度必须与训练数据保持一致
     * @return
     */
	private native float[] svmPredict(long handle, float[] testData, int dim);

    /**
     * 释放句柄，必须与svmInit成对调用，即：调用几次svmInit，必须相应调用几次svmRelease
     * @param handle       // svmInit的返回值
     */
	private native void svmRelease(long handle);

	public static float mse(float[] input, float[] predict)
	{
		float mse_val = 0;
		for (int idx = 0; idx < predict.length; ++idx)
		{
			float diff = input[idx] - predict[idx];
			mse_val += (diff * diff);
		}
		mse_val /= predict.length;
		return mse_val;
	}

    //****************************************** 1D regression test ******************************************
    public static float funcLinear(float x)
    {
        // Linear f(x) = 2x + 1       ---> kernelType = 0
        return 2 * x + 1;
    }

    public static float funcPoly(float x)
    {
        // Ploy   f(x) = x^2 + 1 ---> kernelType = 1
        return 2 * x * x + 1;
    }

    public static float funcRBF(float x)
    {
        // RBF    f(x) = sin(x) + 1    ---> kernelType = 2
        return (float)(Math.sin(x) + 1);
    }

    public static float testSVR1D(int kernelType, int train_num)
    {
        SVMJNI svmjni = new SVMJNI();
        long handle = svmjni.svmInit();

		int dim = 1;
		float[] train_data = new float[train_num];
		float[] train_label  = new float[train_num];

		for(int idx = 0; idx < train_num; idx++)
		{
			train_data[idx] = idx;
			if(0 == kernelType)
			{
			    train_label[idx] = funcLinear(idx);
			}
			else if(1 == kernelType)
			{
			    train_label[idx] = funcPoly(idx);
			}
			else if(2 == kernelType)
			{
			    train_label[idx] = funcRBF(idx);
			}
		}
		svmjni.svmTrain(handle, train_data, train_label, dim,
						103, 1.0, 0.0, 2.0,
						1.0, 0.0, 0.1, kernelType /*LINEAR=0, POLY=1, RBF=2, SIGMOID=3, CHI2=4, INTER=5*/);

		float[] pred = svmjni.svmPredict(handle, train_data, dim);
// 		for(int idx = 0; idx < train_num; ++idx)
// 		{
// 			System.out.println(idx  + " --> " + pred[idx] + "(" + train_label[idx] + ")");
// 		}
        float mse_val = mse(train_label, pred);
        svmjni.svmRelease(handle);
        return mse_val;
    }

    //******************************************  2D regression test ******************************************
    public static float func2DLinear(float x, float y)
    {
        // Linear f(x) = 2x + 2y + 1       ---> kernelType = 0
        return 2 * x + 2 * y + 1;
    }

    public static float func2DPoly(float x, float y)
    {
        // Ploy   f(x) = 2x^2 + 2y^2 + 1 ---> kernelType = 1
        return 2 * x * x + 2 * y * y + 1;
    }

    public static float func2DRBF(float x, float y)
    {
        // RBF    f(x) = sin(x) + cos(y) + 1    ---> kernelType = 2
        return (float)(Math.sin(x) + Math.cos(y) + 1);
    }

    public static float testSVR2D(int kernelType, int train_num)
    {
        SVMJNI svmjni = new SVMJNI();
        long handle = svmjni.svmInit();
        int dim = 2;
        float[] train_data = new float[train_num * train_num * dim];
        float[] train_label  = new float[train_num * train_num];

        for (int idx = 0; idx < train_num; ++idx)
        {
            for (int idy = 0; idy < train_num; ++idy)
            {
                train_data[idx * train_num * dim + dim * idy] = idx;
                train_data[idx * train_num * dim + dim * idy + 1] = idy;

                if(0 == kernelType)
                {
                    train_label[idx * train_num + idy] = func2DLinear(idx, idy);
                }
                else if(1 == kernelType)
                {
                    train_label[idx * train_num + idy] = func2DPoly(idx, idy);
                }
                else if(2 == kernelType)
                {
                    train_label[idx * train_num + idy] = func2DRBF(idx, idy);
                }
            }
        }

        svmjni.svmTrain(handle, train_data, train_label, dim,
                        103, 1.0, 0.0, 2.0,
                        1.0, 0.0, 0.1, kernelType /*LINEAR=0, POLY=1, RBF=2, SIGMOID=3, CHI2=4, INTER=5*/);

        float[] pred = svmjni.svmPredict(handle, train_data, dim);
// 		for(int idx = 0; idx < train_num; ++idx)
// 		{
// 			System.out.println(idx  + " --> " + pred[idx] + "(" + train_label[idx] + ")");
// 		}
        float mse_val = mse(train_label, pred);
        svmjni.svmRelease(handle);
        return mse_val;
    }

   // Test Driver
   public static void main(String[] args)
   {
        int train_num = 8;
        System.out.println("1D Linear regression mse : " + testSVR1D(0, train_num));
        System.out.println("1D Poly   regression mse : " + testSVR1D(1, train_num));
        System.out.println("1D RBF    regression mse : " + testSVR1D(2, train_num));

        System.out.println("2D Linear regression mse : " + testSVR2D(0, train_num));
        System.out.println("2D Poly   regression mse : " + testSVR2D(1, train_num));
        System.out.println("2D RBF    regression mse : " + testSVR2D(2, train_num));
   }
}
