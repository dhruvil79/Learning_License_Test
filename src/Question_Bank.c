#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int num;
const char* readFile()
{
	
    srand(time(0));
    int lower = 1, upper = 5;	
    num = (rand() % (upper - lower + 1)) + lower;		
    switch(num)
    {
    	case 1:
    			return "Question_Bank1.txt";
    			break;
 	    case 2:
    			return "Question_Bank2.txt";
    			break;  	
    	case 3:
    			return "Question_Bank3.txt";
    			break;
    	case 4:
    			return "Question_Bank4.txt";
    			break;
    	case 5:
    			return "Question_Bank5.txt";
    			break;
    	default : 
    			printf("Invalid Input");
    			break;
    }
}
