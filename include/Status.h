/*File that contains the prototypes of status, which it is used for info-storage /
/ about named pipes																*/
#pragma once

typedef struct{
	char** fd_name;		/*2d array with names of receiving data pipes*/
	int* fifo_id;		/*file descriptors for all children			 */	
	int fd_id;			/*file descriptor for sending pipe 			 */
	char* send_pipe;	/*name of sending data pipe 				 */
	int flag;			/*indicated end of receiving data 			 */
}status;

typedef status* Status;	/*pointer to struct*/

Status create_status(int num);	/*create num of receiving pipes	*/

void delete_status(Status s);	/*free all allocated memory 	*/