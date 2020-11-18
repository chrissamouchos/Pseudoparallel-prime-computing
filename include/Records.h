#pragma once	/*Include only once this file*/

typedef struct record record;	/*define customed type record 	*/
typedef record* Record;			/*define pointer to record 		*/

struct record
{
	int number;		/*prime number to be stored 		*/
	float time;		/*time passed for prime to be found	*/
	Record next;	/*pointer to next list item 		*/
};

typedef struct head{	/*wrapper struct with additional info 	*/
	Record next;		/*pointer to first element of list 		*/
	int size;			/*size of items inside list 			*/
}head;

typedef head* Record_info;	/*pointer to wrapper struct 	*/


Record_info create_head(void);						/*create ONLY the pointer to wrapper struct */

Record create_node(int num, float time);			/*create a node with respective values 		*/

void insert_node(Record_info head, Record node);	/*insert created node to simple linked list */

Record insert_after_last(Record last, Record node); /*insert created node after previous last 	*/

void destroy_records(Record_info head);				/*free all the allocated memory 			*/