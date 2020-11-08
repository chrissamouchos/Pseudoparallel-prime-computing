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
	int fd, status;
	char* root_node = "root_node";
	char str[100];
	status = open(root_node, O_RDONLY);
	read(fd, str, sizeof(str));
	printf("Received %s\n", str);
	printf("End of inner node\n");
	close(fd);
	
	return 0;
}