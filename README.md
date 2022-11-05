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
