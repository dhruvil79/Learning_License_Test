#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <ctype.h> 
#include <sys/wait.h>
#include "myheader.h"
#define  Buff_Size 1024
#define  length 2
#define  READ	0      /* The index of the “read” end of the pipe */ 
#define  WRITE	1      /* The index of the “write” end of the pipe */ 

int Right_Ans=0;   
extern int num;
int alarmFlag = 0;
void (*oldhandler)();
extern char str[100];

void childHandler()  /* Executed if the child dies before the parent */ 
{
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("\n\t\t Congratulations , %s !! You'r Pass.\n",str);	
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	exit(/* EXIT SUCCESS */  0); 
}

void alarmHandler() 
{
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	printf("\n\t\tYou have Maximum time reached \n");
	printf("\n\t\tOOPS!! %s , you'r Fail,Better Luck Next Time!!\n",str);
	printf("\n-------------------------------------------------------------------------------------------------------------\n");
	kill( getpid(), SIGINT ); /* Kill  */
	exit(0);
}

int main(void) 
{
    int fd1[2], fd2[2], bytesRead; 
	char message[Buff_Size];
	int Ans_Count=0; 
	char Answer[2]={""};
	pipe(fd1);  
	pipe(fd2);	
	alarm(600);
	oldhandler =signal( SIGALRM, alarmHandler );/* Install signal handler */
	
	oldhandler =signal(SIGCHLD, childHandler);
	int pid=fork();

	if ( pid == 0 ) /*child*/
	{
		close(fd1[WRITE]);  /* Close unused end */
		close(fd2[READ]);  /* Close unused end */
		int counter=0;

		while(counter<15)
		{
			counter++;
			strcpy(Answer,"\0");
			bytesRead= read(fd1[READ], message, Buff_Size );
			printf("\n%s\n",message);
			printf("\nType Answer Here :");
			scanf("\n%s",Answer);
			int Length_of_Ans=strlen(Answer);
			int in_counter=0;
			Answer[0]=toupper(Answer[0]);
			while((Length_of_Ans>1 && in_counter < 3) || (( Answer[0] < 65 || Answer[0] > 68 ) && in_counter <3 ) )
			{
				
				in_counter++;
				printf("\nInvalid Input\n");
				strcpy(Answer,"\0");
				printf("\nType Answer Here : ");
				scanf("%s",Answer);
				Length_of_Ans=strlen(Answer);
				Answer[0]=toupper(Answer[0]);
			}
			if( Length_of_Ans>1 || (Answer[0] < 65 || Answer[0]>68) )
			{
				strcpy(Answer,"T");
			}
			write(fd2[WRITE], Answer,length); 		
		}
		close(fd1[READ]); /* Close used end */
		close(fd2[WRITE]); /* Close used end */
	} 
	else    /*parent*/ 
	{   
		close(fd1[READ]);  /* Close unused end */
		close(fd2[WRITE]);  /* Close unused end */
		printf("\nEnter Your Name : ");
		scanf("%[^\n]%*c",str);
		Instruction();
		printf("\n\t\t\t\t\t: Please Enter for Start your exam :");
		char x=getchar();
	    const char*File_Name=readFile();
		FILE *fp=fopen(File_Name,"r");

		if(fp==NULL)
		{
		        printf("\nCan't open file!!!");
		        exit(0);
    	}
 		else
 		{
	    	char buff[Buff_Size];
	    	int i=0,counter=0;
	    	Ans_Count=0;
	    	char Question[Buff_Size]={""};

	    	while(counter<15)
	    	{
					if(Right_Ans>=11)
					{
						kill( pid, SIGINT ); /* Kill the child */
					}
					else
					{
		    			i=0;
		    			strcpy(Question,"\0");
		   		    	while(i<8)
						{
				    		fgets(buff, Buff_Size, fp);
				    		strcat(Question,buff);	
				    		i++;
						}
						write(fd1[WRITE], Question, strlen(Question)+1); 
						++counter;

						bytesRead= read(fd2[READ], message,length);
						Ans_Count=Check_validate_Ans(message,counter,num);

						if(Ans_Count==1)
						{
							Right_Ans++;	
						}
						if(strcmp(message,"T")==0)
						{
							strcpy(message,"Invalid Input You have Submitted");
						}
						printf("\nAnswer Submited  : %s\n",message );
						
					}
			}
			printf("\n-------------------------------------------------------------------------------------------------------------\n");
			if(Right_Ans>=11)
			{
				printf("\n\t\t Congratulations , %s !! You'r Pass.\n",str);
			}
			else
			{
				printf("\n\t\tOOPS!! %s , you'r Fail,Better Luck Next Time!!\n",str);
			}
			printf("\n-------------------------------------------------------------------------------------------------------------\n");
			fclose(fp);
		}
		close(fd1[WRITE]);  /* Close used end */ 
		close(fd2[READ]);  /* Close used end */	
	}	
}


