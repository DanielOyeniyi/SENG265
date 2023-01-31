/** @file route_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process airline routes.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author Daniel O. 
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void use_case1(char *argv[])
{
	printf("Usecase1");
}

void use_case2(char *argv[])
{
	printf("Usecase2");
}

void use_case3(char *argv[])
{
	printf("Usecase3");
}

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
	switch(argc)				// cases are determined by the number of arguments entered 
	{
		case 4:
		    use_case1(argv);
		    break;
		case 5:
		    use_case2(argv);
		    break;	
		case 6:
		    use_case3(argv);
		    break;
	}
    exit(0);
}
