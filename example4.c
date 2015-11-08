#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
void usr1_handler( int sig_num){
	printf("Parent (%d) got the SIGUSR1\n", getpid() );
}
int main(){
	pid_t ret;
	int status;
	int role = -1;
	ret = fork();
	if( ret > 0){//当前进程为父进程
		printf("Parent: This is the parent process (pid %d)\n",getpid() );
		signal( SIGINT, usr1_handler);//为usr1_handler注册信号句柄
		role = 0;
		pause();//等待信号
		printf("Parent: Awaiting child exit\n");
		ret = wait( &status);//等待子进程退出
	}  
	else 
		if(ret == 0) {//当前进程为子进程
			printf("Child: This is the child process (pid %d)\n",  getpid());
			role = 1;
			sleep(1);
			printf("Child: Sending SIGUSR1 to pid %d\n", getppid());
			kill(getppid(), SIGUSR1);//向父进程发送SIGUSR1信号
			sleep(2);
		 }
		else {
		 	printf("Parent: Error trying to fork() (%d)\n", errno);
		 }
			printf("%s: Exiting…\n", ( ( role == 0) ? "Parent" : "Child"));
	return 0;
}



