/* Copyright © 2021 Michael Simonsen
 * Programnavn: primes
 */
/* printf("%-16d",i); */
   
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


FILE *myfile;
int i = 2;


/* Signal Handler for SIGINT */
void sigint_handler(int sig_num)
{
    /* Reset handler to catch SIGINT next time. */
    setbuf(stdout, NULL);
    printf("\nInterrupt signal (%d) received.\n",sig_num);
    printf("Processing: %d\n",i);
	printf("Saving progress to prime.ini\n");
    myfile = fopen ("prime.ini","w");
	fprintf(myfile,"%d",i);
	fclose(myfile);
	printf("File saved, now terminating !\n");
/* Do a graceful cleanup of the program like: free memory/resources/etc and exit */
    exit(0);
}

int main()
{
   signal(SIGINT, sigint_handler);
/* Remove cout buffer */
   setbuf(stdout, NULL);
   
   int num1 = 2;
   int num2 = 2147483647;
   int flag_var, j;
   
   
/* check if config file exist */
	myfile=fopen ("prime.ini","r");
	if (myfile)
	{
		printf("config file exists\n");
		printf("reading: prime.ini\n");
		fscanf(myfile,"%d",&i);
		fclose(myfile);
		num1=i;
		
		printf("continuing with: %d\n\n",num1);
	}
	else
/* create config file */
	{
		printf("prime.ini doesn't exist\n");
		printf("creating it now\n");
		myfile = fopen ("prime.ini","w");
		fprintf(myfile,"%d",2);
		fclose(myfile);
		puts("done");
	}
 
/* Display prime numbers for input range */
   printf("Prime numbers from %d to %d are:\n", num1, num2);
   for(i=num1+1; i<num2; ++i)
   {
      flag_var=0;
      for(j=2; j<=i/2; ++j)
      {
         if(i%j==0)
         {
            flag_var=1;
            break;
         }
      }
      if(flag_var==0)
      
         printf("%-20d",i);
  }
  return 0;
}
