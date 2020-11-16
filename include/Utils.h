#pragma once /*Include only once*/

/*----------------START OF RANGE-----------------------*/
typedef struct
{
	int range;			/*range to sign to each child 			*/
	int remainder;		/*remainder to be signed to last process*/
}range;

typedef range* Range;	/*pointer to struct range*/

Range range_create(int range, int remainder);			/*create a struct and assign given values	*/

void range_delete(Range range);							/*free all allocated space 					*/

void range_change(Range r, int range, int remainder);	/*change values of r struct with new  		*/
/*----------------END OF RANGE--------------------------*/

/*----------------- VARIOUS FUNCTIONS-------------------*/
void usage(const char* command);	/*Print expected format*/

Range find_range(int NumOfChildren, int n, int m); /*Split the numeric range*/

void split_n_exec(int n, int m, int NumOfChildren, char* executable, pid_t pid); /*Split to proper values then call and execute childer 	*/
/*----------------- END OF FUNCTIONS--------------------*/