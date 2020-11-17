/*arguments for exec* nameofexec, low, up, numof, is, sroot_id	 /
/								0,	1,	2,		3,	4,	5		*/

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

#include "Utils.h"
#include "Status.h"
#include "Records.h"

int main(int argc, char** argv){
	pid_t pid;
	pid = getpid();
	int low, up, numof, is, sroot_id;
	low = atoi(argv[1]);
	up = atoi(argv[2]);
	numof = atoi(argv[3]);
	is = atoi(argv[4]);
	sroot_id = atoi(argv[5]);

	Status s = create_status(numof);

	/*--------------Open pipe to send----------------------*/
	sprintf(s -> send_pipe, "in%d", is);
	s -> fd_id = open(s -> send_pipe, O_WRONLY);

	Record_info r = create_head();
	/*-----------------Read info---------------------------*/

	char* executable = "./leaf";
	printf("inner node with id: %d\n", pid);

	/*--------------Create and open pipes to read----------*/
	for(int i = 0; i < numof; i++){
		sprintf(s -> fd_name[i], "le%d", i);
		if(mkfifo(s -> fd_name[i], 0666) < 0)
			perror("Error, pipe creation");
	}
	
	split_n_exec(low, up, numof, executable, sroot_id);
	
	for(int i = 0; i < numof; i++)
		s -> fifo_id[i] = open(s -> fd_name[i], O_RDONLY);

	/*---------------Unlink all fifos----------------------*/
	for(int i = 0; i < numof; i++){
		close(s -> fifo_id[i]);
		unlink(s -> fd_name[i]);
	}

	while(wait(NULL)>0);
	delete_status(s);
	destroy_records(r);
	
	return 0;
}