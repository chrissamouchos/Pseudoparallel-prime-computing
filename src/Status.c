#include <stdlib.h>

#include "Status.h"

Status create_status(int num){
	Status s = malloc(sizeof(status));
	s -> flag = 0;
	s -> send_pipe = malloc(sizeof(char)*2 + 10);
	s -> fd_name = malloc(sizeof(char*)*num);
	for(int i = 0; i < num; i++)
		s -> fd_name[i] = malloc(sizeof(char)*2 + 10);
	s -> fd_id = 0;
	s -> fifo_id = malloc(sizeof(int)*num);
	return s;
}

void delete_status(Status s){
	free(s -> send_pipe);
	for(int i = 0; i < s -> flag; i++)
		free(s -> fd_name[i]);
	
	free(s -> fifo_id);
	free(s -> fd_name);
	free(s);
}