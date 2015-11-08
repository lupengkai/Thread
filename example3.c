#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void  catch_ctlc( int sig_num) {
	printf("Caught Control-C\n");
	fflush(stdout);
}

int main() {
	signal(SIGINT, catch_ctlc);//signal函数为进程注册信号句柄（一种回调函数，是通过函数指针调用函数。）SIGINT 键盘中断
	printf("Go head, make my day.\n");
	pause();//将进程挂起，直到收到信号。如果进程捕获的信号已经注册了信号句柄，那么pause函数会在信号句柄被调用并返回后才返回。
	return 0;
}