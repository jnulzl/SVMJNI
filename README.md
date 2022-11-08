# Support Vector Machine C/C++/jni interface

## For Ubuntu 16/18/20.4

- Install OpenCV/JDK

```shell
>>sudo apt update 
>>sudo apt install libopencv-dev
>>sudo apt install openjdk-8-jdk openjdk-8-jre openjdk-8-source
```

- Build

`ROOT` is the directory of README.md

```shell

>>mkdir $ROOT/build && cd build
>>cmake ../ -DCMAKE_BUILD_TYPE=Release # -DSYSTEM_NAME=Linux/-DSYSTEM_NAME=Android 
>> make VERBOSE=1 -j4
```

- Demo

C/C++/java demo sources in `examples` directory.

`ROOT` is the directory of README.md.


```shell
# c demo
>>cd $ROOT/bin/Linux
>>./demo_c
# java demo
>>cd $ROOT/examples
>>javac SVMJNI.java && java -Djava.library.path=../bin/Linux  SVMJNI
```

- Reference

  - [Java Programming Tutorial Java Native Interface (JNI)](https://www3.ntu.edu.sg/home/ehchua/programming/java/javanativeinterface.html#zz-4.1)

  - [Java Programming Tutorial Java Native Interface (JNI)中文翻译](https://blog.csdn.net/createchance/article/details/53783490)

  - [Java中调用native API和通过JNI的方式去调用C++代码，本质有什么区别么？](https://www.zhihu.com/question/54397475/answer/2130664220)

  - [The Java™ Native Interface Programmer’s Guide and Specification](https://www.uni-ulm.de/fileadmin/website_uni_ulm/iui.inst.200/files/staff/domaschka/misc/jni_programmers_guide_spec.pdf)

  - [Java Native Interface Specification Contents](https://docs.oracle.com/en/java/javase/16/docs/specs/jni/index.html)





