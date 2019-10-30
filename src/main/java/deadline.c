#include "Deadline.h"
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
 static int runtime=90;

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
JNIEXPORT void JNICALL Java_Deadline_sleep(JNIEnv *env, jobject obj)
{
	sleep(1);
}

JNIEXPORT void JNICALL Java_Deadline_printSchedType(JNIEnv *env, jobject obj)
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

JNIEXPORT void JNICALL Java_Deadline_setSchedType(JNIEnv *env, jobject obj)
{
		// printf("Here\n");
		struct sched_attr attr;
		unsigned int flags = 0;

		attr.size = sizeof(attr);
		attr.sched_flags = SCHED_FLAG_RESET_ON_FORK;
		attr.sched_nice = 0;
		attr.sched_priority = 0;
		attr.sched_policy = SCHED_DEADLINE;
		attr.sched_runtime = 60*1000*1000;
		attr.sched_period = 100*1000*1000;
		attr.sched_deadline= 60*1000*1000;
		int ret=sched_setattr(0, &attr, flags);
		if(ret!=0){
			perror("\nsetSched: ");
		}

}

JNIEXPORT void JNICALL Java_Deadline_sayHi
(JNIEnv *env, jobject obj, jstring string) {
	 printf("Hello World!\n");
   return;

}

JNIEXPORT void JNICALL Java_Deadline_getchildPIDs(JNIEnv *env, jobject obj){
	FILE *fptr;
	int pid=getpid();
	char *line = NULL;
   size_t len = 0;
   ssize_t nread;
	char PID[256];
	char command []="pgrep -P ";
	snprintf (PID, sizeof(PID), "%d",pid);
	strcat(command,PID);
	strcat(command," >pids.txt");
	system(command);
	if ((fptr = fopen("pids.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);         
    }
    while ((nread = getline(&line, &len, fptr)) != -1) {
               
               struct sched_attr attr;
				unsigned int flags = 0;
				int pid=0;

				attr.size = sizeof(attr);
				attr.sched_flags = SCHED_FLAG_RESET_ON_FORK;
				attr.sched_nice = 0;
				attr.sched_priority = 0;
				attr.sched_policy = SCHED_DEADLINE;
				attr.sched_runtime = 60*1000*1000;
				attr.sched_period = 100*1000*1000;
				attr.sched_deadline= 100*1000*1000;
               
               
        		pid=strtol(line,NULL,10);
        		// printf("%d\n",pid );
        		int ret=sched_setattr(pid, &attr, flags);
        		// perror("Return");

           }

}

JNIEXPORT void JNICALL Java_Deadline_getParentPIDs(JNIEnv *env, jobject obj){
	FILE *fptr;
	int pgid=getpgid(getpid());
	char *line = NULL;
   size_t len = 0;
   ssize_t nread;
	char PGID[256];
	char command []="pgrep -g ";
	printf("PGID : %d\n",pgid );
	snprintf (PGID, sizeof(PGID), "%d",pgid);
	strcat(command,PGID);
	strcat(command," >>pgids.txt");
	system(command);
	if ((fptr = fopen("pgids.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);         
    }
    while ((nread = getline(&line, &len, fptr)) != -1) {
               struct sched_attr attr;
				unsigned int flags = 0;
				int pid=0;

				// attr.size = sizeof(attr);
				// attr.sched_flags = SCHED_FLAG_RESET_ON_FORK;
				// attr.sched_nice = 0;
				// attr.sched_priority = 0;
				// attr.sched_policy = SCHED_DEADLINE;
				// attr.sched_runtime = 60*100;
				// attr.sched_period = 100*100;
				// attr.sched_deadline= 100*100;
               
               
        		pid=strtol(line,NULL,10);
        		printf("%d\n",pid );
    //     		int ret=sched_setattr(pid, &attr, flags);
    //     		// perror("Return");

           }

}

JNIEXPORT void JNICALL Java_Deadline_printPID
(JNIEnv *env, jobject obj) {
	 printf("%d",getpid());
   return;

}
JNIEXPORT jint JNICALL Java_Deadline_getPID
(JNIEnv *env, jobject obj) {
// const char *str = (*env)->GetStringUTFChars(env, string, 0);
// char cap[128];
// strcpy(cap, str);
// printf(“Hello %s”, str);
// (*env)->ReleaseStringUTFChars(env, string, str);
	 // printf("%d\n",getpid());
   return getpid();

}
JNIEXPORT void JNICALL Java_Deadline_cgroup_classify
(JNIEnv *env, jobject obj) {
	// char cpu_grp[100];
	// sprintf(cpu_grp,"sudo cgclassify -g cpu:group_p %d\n",getpid());
	// // printf("%s\n",cpu_grp);
	// system(cpu_grp);
}


JNIEXPORT void JNICALL Java_Deadline_scheduleAll
(JNIEnv *env, jobject obj) {
	FILE *fptr;
	char *line = NULL;
   size_t len = 0;
   ssize_t nread;
	char command []="ps --no-headers -fT -C java |awk {'print $3'} > pid.txt";
	system(command);
	if ((fptr = fopen("pid.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);         
    }
    printf("Scheduling\n");
    while ((nread = getline(&line, &len, fptr)) != -1) {
               
               struct sched_attr attr;
				unsigned int flags = 0;
				int pid=0;

				attr.size = sizeof(attr);
				attr.sched_flags = SCHED_FLAG_RESET_ON_FORK;
				attr.sched_nice = 0;
				attr.sched_priority = 0;
				attr.sched_policy = SCHED_DEADLINE;
				attr.sched_runtime = runtime*1000*1000;
				attr.sched_period = 100*1000*1000;
				attr.sched_deadline= runtime*1000*1000;
               
               
        		pid=strtol(line,NULL,10);
        		// printf("%d\n",pid );
        		int ret;

        		do{
					 ret=sched_setattr(pid, &attr, flags);
					 attr.sched_runtime-=10*1000*1000;
					 
					usleep(100000);
					if(ret<0){
						// perror("Scheduling");
						printf("%d, %d\n",gettid(),attr.sched_runtime );
					}
				}
				while(ret<0 && attr.sched_runtime>0);
				if(attr.sched_runtime<=0 && runtime>10){
					runtime=runtime-10;

				}

           }


	
}