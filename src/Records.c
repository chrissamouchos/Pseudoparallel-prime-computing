/*Source code for basic list functions 	*/
#include <stdlib.h> 		/*for malloc*/

#include "Records.h"	/*my functions	*/

Record_info create_head(void){
	Record_info r = malloc(sizeof(head));
	
	/*Initialize values to default*/
	r -> next = NULL;
	r -> size = 0;

	return r;
}

Record create_node(int num, float time){
	Record r = malloc(sizeof(record));

	/*Initialize slots, with given values*/
	r -> number = num;
	r -> time = time;
	r -> next = NULL;

	return r;
}

void insert_node(Record_info head, Record node){
	head -> size = (head -> size)++;	/*increase size of list by 1 		*/
	Record temp =  head -> next;		/*current node to traverse the list	*/
	Record prev = NULL;					/*store prev node 					*/
	
	if(temp == NULL){					/*if list is empty 					*/
		head -> next = node;
		return;
	}
	while(temp != NULL){	/*2 cases*/
		if(node -> number < temp -> number){	/*intermediate of list*/
			prev -> next = node;
			node -> next = temp;
			return;
		}

		/*update values of pointers*/
		prev = temp;			/*store prev 				*/
		temp = temp -> next;	/*make temp show next node 	*/
	}
	prev -> next = node; /*add node to the end of list*/
	return;
}

void destroy_records(Record_info head){
	Record temp = head -> next;			/*store head of list 				*/
	Record to_destroy = head -> next;	/*pointer to node to be destroyed 	*/
	
	/*destroy all nodes except record_info*/
	while(to_destroy != NULL){
		temp = to_destroy -> next;		
		free(to_destroy);				/*free node*/
		to_destroy = temp;
	}
	free(head);	/*destroy record_info*/
}