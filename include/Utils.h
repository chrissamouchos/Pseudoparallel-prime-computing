#pragma once /*Include only once*/

/*----------------START OF RANGE-----------------------*/
typedef struct
{
	int range;
	int remainder;
}range;

typedef range* Range;

Range range_create(int range, int remainder);

void range_delete(Range range);

void range_change(Range r, int range, int remainder);
/*----------------END OF RANGE--------------------------*/

/*----------------- VARIOUS FUNCTIONS-------------------*/
void red();							/*Chane printing color to red 	*/

void green();						/*Chane printing color to green	*/

void cyan();						/*Change printing color to cyan */

void reset();						/*Reset color to default		*/

void usage(const char* command);	/*Print expected format 		*/

Range find_range(int NumOfChildren, int n, int m); /*Split the numeric range*/

void split_n_exec(int n, int m, int NumOfChildren, char* executable);/*Split to proper values then call and execute childer 	*/

/*----------------- END OF FUNCTIONS--------------------*/