/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class HelloWorld */

#ifndef _Included_HelloWorld
#define _Included_HelloWorld
#ifdef __cplusplus
extern "C" {
#endif
#undef HelloWorld_MIN_PRIORITY
#define HelloWorld_MIN_PRIORITY 1L
#undef HelloWorld_NORM_PRIORITY
#define HelloWorld_NORM_PRIORITY 5L
#undef HelloWorld_MAX_PRIORITY
#define HelloWorld_MAX_PRIORITY 10L
/*
 * Class:     HelloWorld
 * Method:    sayHi
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_HelloWorld_sayHi
  (JNIEnv *, jobject, jstring);

/*
 * Class:     HelloWorld
 * Method:    printPID
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_HelloWorld_printPID
  (JNIEnv *, jobject);

/*
 * Class:     HelloWorld
 * Method:    getPID
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_HelloWorld_getPID
  (JNIEnv *, jobject);

/*
 * Class:     HelloWorld
 * Method:    printSchedType
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_HelloWorld_printSchedType
  (JNIEnv *, jobject);

/*
 * Class:     HelloWorld
 * Method:    setSchedType
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_HelloWorld_setSchedType
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
