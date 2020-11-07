#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>		/* For file descriptors */
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char** argv){
	pid_t pid;
	int status, fd;
	char* root_node = "root_node";
	status = mkfifo(root_node, 0666);
	if(status < 0) perror("Pipe creation error");

	char* buff = malloc(sizeof(char)*20);
	buff = "Hello from parent!\n";

	if((pid = fork()) < -1){
		perror("Fork error");
		exit(1);
	}

	if(pid == 0){
		printf("Creating inner_node...\n");
		execl("./inner_node", "inner_node", NULL);
	}
	else{
		printf("I am parent!\n");
		if(fd = open("root_node", O_WRONLY) < 0)
			perror("Error open pipe");
		if(fd = write(fd, buf, strlen(buf)) != strlen(buf))
			perror("Error write in pipe");
		wait(NULL);
	}
	close(fd);
	return 0;
}