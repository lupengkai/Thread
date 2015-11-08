#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
int main(){
	pid_t ret;
	int status, i;
	int role = -1;
	ret = fork();//创建子进程
	if (ret > 0) { //大于0为父进程
		printf("Parent: This the parent process (pid %d)\n", getpid());
		for (i=0; i<6; i++) {
			printf("Parent:At count %d\n", i);
			sleep(1);
		}
		ret = wait(&status);//将进程挂起直到子进程退出，返回退出的子进程的pid值
		role=0;
	} 

	else 
		if (ret == 0) {//等于0为新创建的子进程
			printf("Child: This the child process (pid %d)\n", getpid());
			for (i=0; i<6; i++) {
				printf("Child: At count %d \n",i);
				sleep(1);
			}

			role = 1;
		} 

	else {//小于0说明发生错误
			printf("Parent:Error trying to fork() (%d)\n",errno);
		 }

	printf("%s:Exiting...\n", ((role == 0)?"Parent":"Child"));
	return 0;
}



