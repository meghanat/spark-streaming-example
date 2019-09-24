#include "HelloWorld.h"
#include<string.h>
#include<stdio.h>
#include<jni.h>
#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>
#include<linux/sched.h>
#include <string.h>
#include <time.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <string.h>
#include <math.h>



#define gettid() syscall(__NR_gettid)

 #define SCHED_DEADLINE	6

 /* XXX use the proper syscall numbers */
 #ifdef __x86_64__
 #define __NR_sched_setattr		314
 #define __NR_sched_getattr		315
 #endif

 #ifdef __i386__
 #define __NR_sched_setattr		351
 #define __NR_sched_getattr		352
 #endif

 #ifdef __arm__
 #define __NR_sched_setattr		380
 #define __NR_sched_getattr		381
 #endif

 static volatile int done;

 struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
 };

 int sched_setattr(pid_t pid,
		  const struct sched_attr *attr,
		  unsigned int flags)
 {
	return syscall(__NR_sched_setattr, pid, attr, flags);
 }

 int sched_getattr(pid_t pid,
		  struct sched_attr *attr,
		  unsigned int size,
		  unsigned int flags)
 {
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
 }

JNIEXPORT void JNICALL Java_HelloWorld_printSchedType(JNIEnv *env, jobject obj)
{
        int schedType;

        schedType = sched_getscheduler(getpid());
        switch(schedType)
        {
                case SCHED_FIFO:
                printf("Pthread Policy is SCHED_FIFO : %d \n",schedType);
                break;
                case SCHED_OTHER:
                printf("Pthread Policy is SCHED_OTHER : %d \n",schedType);
                break;
                case SCHED_RR:
                printf("Pthread Policy is SCHED_RR : %d \n",schedType);
                break;
               	case SCHED_DEADLINE:
                printf("Pthread Policy is SCHED_DEADLINE : %d \n",schedType);
                break;
                default:
                printf("Pthread Policy is UNKNOWN : %d \n",schedType);

        }

}

JNIEXPORT void JNICALL Java_HelloWorld_setSchedType(JNIEnv *env, jobject obj)
{
		printf("Here\n");
		struct sched_attr attr;
		unsigned int flags = 0;

		attr.size = sizeof(attr);
		attr.sched_flags = SCHED_FLAG_RESET_ON_FORK;
		attr.sched_nice = 0;
		attr.sched_priority = 0;
		attr.sched_policy = SCHED_DEADLINE;
		attr.sched_runtime = 0.95*10*100*1000;
		attr.sched_period = 10*100*1000;
		attr.sched_deadline=10*100*1000;
		printf("Here too\n");
		if(sched_setattr(0, &attr, flags)!=0){
			perror("Failed");	
		}
		printf("Here three\n");
		// printf("Scheduler changed");
		// int num,j;
		// for(j=0;j<100000000;)
		// {
		// 	num = 12/1822*4386384348/579849;
		// 	num = 12/1822*4386384348/579849;
		// 	num = 12/1822*4386384348/579849;
		// }
}
JNIEXPORT void JNICALL Java_HelloWorld_sayHi
(JNIEnv *env, jobject obj, jstring string) {
// const char *str = (*env)->GetStringUTFChars(env, string, 0);
// char cap[128];
// strcpy(cap, str);
// printf(“Hello %s”, str);
// (*env)->ReleaseStringUTFChars(env, string, str);
	 printf("Hello World!\n");
   return;

}

JNIEXPORT void JNICALL Java_HelloWorld_printPID
(JNIEnv *env, jobject obj) {
// const char *str = (*env)->GetStringUTFChars(env, string, 0);
// char cap[128];
// strcpy(cap, str);
// printf(“Hello %s”, str);
// (*env)->ReleaseStringUTFChars(env, string, str);
	 printf("%d\n",getpid());
   return;

}
JNIEXPORT jint JNICALL Java_HelloWorld_getPID
(JNIEnv *env, jobject obj) {
// const char *str = (*env)->GetStringUTFChars(env, string, 0);
// char cap[128];
// strcpy(cap, str);
// printf(“Hello %s”, str);
// (*env)->ReleaseStringUTFChars(env, string, str);
	 // printf("%d\n",getpid());
   return getpid();

}
JNIEXPORT void JNICALL Java_HelloWorld_cgroup_classify
(JNIEnv *env, jobject obj) {
	
}