#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	pid_t pid;
	int fd[2];
	pipe(fd);

	char buf[1];
	if((pid = fork()) == -1) perror("Fork error");
	if(pid == 0){
		printf("I am child: %d\n", pid);
		close(fd[1]);
		read(fd[0], buf, 1);
		printf("i found : %d\n", buf[0]);
		execl("./inner_node", "inner_node", NULL);
	}
	else{
		printf("I am parent!\n");
		close(fd[0]);
		char i = 2;
		buf[0] = i;
		write(fd[1], buf, 2);
		wait(NULL);
	}
	close(fd[1]);
	return 0;
}