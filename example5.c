#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void *myThread(void *arg){ //线程运行的函数
	printf("Thread ran\n");
	pthread_exit(arg);//终止调用这个函数的线程并返回？。
	printf("Thread is runing?");
	//pthread.self()获得自己的线程描述符 转化为int类型之后可变为pid
}

int main(){
	int ret,i;
	pthread_t mythread;
	ret = pthread_create( &mythread, NULL, myThread, NULL);//创建线程，成功返回0
// 第一个参数为指向线程标示符的指针。
// 第二个参数用来设置线程属性。
// 第三个参数是线程运行的函数的起始地址。
// 最后一个参数是运行函数的参数。
	sleep(5);
	if(ret != 0){//创建失败
		printf("Can not create pthread (%s)\n", strerror(errno));
		exit(-1);        
	}

	for (i = 0; i<3; i++) {
		printf("This is the main process\n");
		//pthread_join(mythread, NULL);
	}
	return 0;
}

//gcc example5.c -lpthread -o example5
