#include <pthread.h>
#include <stdio.h>
#include <assert.h>
pthread_mutex_t cntr_mutex = PTHREAD_MUTEX_INITIALIZER;//创建一个互斥变量，快速互斥。
long protVariable = 0L;

void *myThread(void *arg){//每个线程执行10000次protVariable变量加一。
	int i, ret;
	for(i=0; i<10000; i++){
		ret = pthread_mutex_lock( &cntr_mutex );
		assert( ret == 0 );
		protVariable++;//防止这个变量被同时访问把增大这个变量的语句放入关键区，即在此句代码前加锁，执行完后解锁。
		ret = pthread_mutex_unlock( &cntr_mutex );
		assert( ret == 0 );
	}
	pthread_exit(NULL);
}

#define MAX_THREADS 10
int main(){
	int ret, i;
	pthread_t threadIds[MAX_THREADS];

	for(i=0; i<MAX_THREADS; i++){//创建MAX_THREADS个子进程并运行。
		ret = pthread_create( &threadIds[i], NULL, myThread, NULL);
		if(ret != 0){
			printf("Error creating thread %d\n", (int)threadIds[i]);
		}
	}

	for(i = 0; i<MAX_THREADS; i++){//依次执行子进程
		ret = pthread_join( threadIds[i], NULL);
		if(ret != 0){
			printf("Error joining thread %d\n", (int)threadIds[i]);
		}
	}

	printf("The protected variable value is %ld\n", protVariable);
	ret = pthread_mutex_destroy( &cntr_mutex );//销毁互斥变量，如果互斥锁正被锁定，函数会失败，并返回错误码。

	if(ret != 0 ){
		printf("Could not destroy the mutex\n");
	}
	return 0;
}

