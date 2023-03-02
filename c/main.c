/* Copyright © 2021 Michael Simonsen
   Programname: primes */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>

FILE *myfile;
unsigned long long i = 2;
unsigned long long j;
unsigned long long num1 = 2;
unsigned long long num2 = 18446744073709551615U;
/*unsigned long long num2 = 200;*/
unsigned long long flag_var;

/* Signal Handler for SIGINT */
void sigint_handler(int sig_num)
{
    setbuf(stdout, NULL);
    printf("\nInterrupt signal (%d) received.\n",sig_num);
    printf("Processing: %llu\n",i);
	printf("Saving progress to prime.ini\n");
    myfile = fopen ("prime.ini","w");
	fprintf(myfile,"%llu\n",i);
	fclose(myfile);
	printf("File saved, now terminating !\n");
    exit(0);
}

int main()
{
   signal(SIGINT, sigint_handler);
/* Remove cout buffer */
   setbuf(stdout, NULL);
   
/* check if config file exist */
	myfile=fopen ("prime.ini","r");
	if (myfile)
	{
		printf("config file exists\n");
		printf("reading: prime.ini\n");
		fscanf(myfile,"%llu",&i);
		fclose(myfile);
		num1=i;
		printf("continuing with: %llu\n\n",num1);
	}
	else
/* create config file */
	{
		printf("prime.ini doesn't exist\n");
		printf("creating it now\n");
		myfile = fopen ("prime.ini","w");
		fprintf(myfile,"%d\n",2);
		fclose(myfile);
		puts("done");
	}

/* Calculate and display prime numbers */
   printf("Prime numbers from %llu:\n", num1);
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
         printf("%-24llu",i);
  }
  return 0;
}
