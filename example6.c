#include <pthread.h>
#include <stdio.h>

void *myThread(void *arg){
	printf("Thread %d started\n", (int)arg);
	pthread_exit(arg);
}

#define MAX_THREADS 5

int main(){
	int ret, i, status;
	pthread_t threadIds[MAX_THREADS];//创建进程描述符
	for(i = 0; i<MAX_THREADS; i++){//创建5个线程
		ret = pthread_create(&threadIds[i], NULL, myThread, (void*)i);//创建进程
		if(ret != 0){
			printf("Error creating thread %d\n", i);
		}
	}
	for(i = 0; i<MAX_THREADS; i++){//依次执行每个线程并返回终止状态。
		ret = pthread_join(threadIds[i], (void **)&status);//挂起调用该函数的调用者直到加入的线程完成。
		if(ret != 0){
			printf("Error joining thread %d\n", i);
		}
		else{
			printf("Status = %d\n", status);
		}
	}
	return 0;
}
