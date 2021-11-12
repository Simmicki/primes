// Copyright © 2021 Michael Simonsen
// Programnavn: Primes

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <csignal>

using namespace std;

unsigned long long isPrimeNumber(unsigned long long);
void signalHandler(int);

unsigned long long n = 2;

int main()
{
   
   bool isPrime;
   unsigned long long startnum;
   unsigned long long endnum = 18446744073709551615u;
   string line;
   
   // register signal SIGINT and signal handler  
   signal(SIGINT, signalHandler);
   
   // open "prime.ini" if it exists
   ifstream myfile;
   myfile.open("prime.ini");

   if(myfile) {
      cout << "config file exists" << endl;
      cout << "reading: prime.ini" << endl;
      while ( getline (myfile,line) )
    {
      stringstream ss;  
      ss << line;  
      ss >> startnum;
    }
    myfile.close();
    cout << "continuing with: " << startnum << endl << endl;
    
   } else {
      cout << "prime.ini doesn't exist" << endl;
      cout << "creating it now" << endl;
      ofstream myfile;
      myfile.open("prime.ini");
      myfile << "2" << endl;
      myfile.close();
      cout << "done" << endl << endl;
      startnum = 2;
   }
   
   for(n = startnum; n < endnum; n++) {
      // isPrime will be true for prime numbers
      isPrime = isPrimeNumber(n);

      if(isPrime == true){
         cout<<left<<setw(20)<<n;
         
	  }
   }
   return 0;
}

// Function that checks whether n is prime or not
unsigned long long isPrimeNumber(unsigned long long n) {
   bool isPrime = true;

   for(int i = 2; i <= n/2; i++) {
      if (n%i == 0) {
         isPrime = false;
         break;
      }
   }  
   return isPrime;
}

void signalHandler( int signum ) {
   cout << endl << "Interrupt signal (" << signum << ") received." << endl;

   // cleanup and close up stuff here  
   // terminate program
   cout << "Saving progress to prime.ini" << endl;
   ofstream myfile;
   myfile.open("prime.ini");
   myfile << n << endl;
   myfile.close();

   cout << "File saved, now terminating !";
   exit(signum);  
}

