
 /* Group 3:
 * Siddharth Banerjee 002111001097
 * Tanmay Roy 002111001017
 * Anupam Ghosh 002111001102
 * Vikash Sangai 002111001100
 * Date: 28/08/23
*/
 
 /*
  * Question:
  * The objective of this assignment is to create a deadlock. For this purpose define two
global variables (Total_1 and Total_2) and initialize both of them to 1000. You
should also have two mutexes to protect these two global variables. You need to
create two threads also.
 * The function of each of the threads is to generate a random quantity (not more than
50) and subtract that quantity from one of the Total and add that quantity to the
other Total. While manipulating the Totals, each Thread should lock both the mutex
and then unlock it after changing the Totals.
  * */

 /*
  * Compilation instructions:
  * gcc -Wall -g -o deadlock 03-5.c -lpthread
  * ./deadlock
  * */

 /*
  * Output:
                        -------STATUS-------
                        Total_1: 966
                        Total_2: 1034
                        Sum of the two totals: 2000

                        -------STATUS-------
                        Total_1: 966
                        Total_2: 1034
                        Sum of the two totals: 2000

                        -------STATUS-------
                        Total_1: 1025
                        Total_2: 975
                        Sum of the two totals: 2000

                        -------STATUS-------
                        Total_1: 1013
                        Total_2: 987
                        Sum of the two totals: 2000

                        -------STATUS-------
                        Total_1: 1060
                        Total_2: 940
                        Sum of the two totals: 2000

                        -------STATUS-------
                        Total_1: 1026
                        Total_2: 974
                        Sum of the two totals: 2000

                        -------STATUS-------
                        Total_1: 1022
                        Total_2: 978
                        Sum of the two totals: 2000

                        -------STATUS-------
                        Total_1: 1052
                        Total_2: 916
                        Sum of the two totals: 1968
^C

  * */

/*
 * DEADLOCK CAUSATION:
 * 
 * This program involves the usage of two lcoks- mutex1 and mutex2, to enforce mutual exclusion
 * between two threads t1 and t2.
 *
 * The issue arises due to the order in which the locks are acquired by the two threads.
 * 
 * t1 acquires mutex1 first, subtracts a randomly generated total from Total_1, then acquires mutex2
 * and adds the amount subtracted from Total_1 to Total_2. Both locks are released together after this.
 *
 *
 * t2 acquires mutex2 first, subtracts a randomly generated total from Total_2, then acquires mutex1
 * and adds the amount subtracted from Total_2 to Total_1. Both locks are released together after this.
 *
 * This may cause the two threads t1 and t2 to deadlock, with one thread needing the lock the other is
 * holding to proceed, causing the program to halt.
 *
 * DEADLOCK AVOIDANCE:
 * 
 * A simple way to avoid this form of deadlock is to fix the order in which threads acquire locks.
 * 
 * Either mutex1 or mutex2 are both acquired first by each thread. Thus, one thread would have to wait
 * before it can acquire any lock, and thus prevent deadlocks
 *
 * 
 * Another method to enforce deadlock locking is 2 phase locking: 
 * 
 * Each thread acquired all the locks it needs together (growing phase).
 * 
 * It then releases them together after performing its operations. 
 * 
 * This would prevent any scope of a deadlock between the threads, since all required locks 
 * are acquired at once by a thread that needs them.
 * */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

int Total_1 = 1000;
int Total_2 = 1000;

	// Generates a random number between lowerCap and higherCap
int randomNumberGenerator(int lowerCap, int higherCap)		
{
	int difference = higherCap - lowerCap;
	int randomNumber = lowerCap + rand() %  (difference + 1);

	return randomNumber;
}

//contains print statements for showing the status of the threads
void* sum()
{
  printf("\n\t\t\t-------STATUS-------\n");
  printf("\t\t\tTotal_1: %d\n", Total_1);
  printf("\t\t\tTotal_2: %d\n", Total_2);
  int Total = Total_1+Total_2;
  printf("\t\t\tSum of the two totals: %d\n", Total);

  return NULL;
}

// function for t1
void* first()
{

  pthread_mutex_lock(&mutex1);

  int rng;
  rng = randomNumberGenerator(0, 50);

  Total_1-=rng;
  pthread_mutex_lock(&mutex2);
  Total_2+=rng;
  pthread_mutex_unlock(&mutex2);
  pthread_mutex_unlock(&mutex1);


  return NULL;
}

//function for t2
void* second()
{

  pthread_mutex_lock(&mutex2);

  int rng;
  rng = randomNumberGenerator(0, 50);

  Total_2-=rng;
  pthread_mutex_lock(&mutex1);
  Total_1+=rng;
  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);

  return NULL;
}


int main()
{
  pthread_mutex_init(&mutex1,NULL);
  pthread_mutex_init(&mutex2,NULL);

  //seeding the random number generator
  srand((unsigned) time(0));

  pthread_t t1,t2,control;

  while(true)
  {
    pthread_create(&t1,NULL,first,NULL);
    pthread_create(&t2,NULL,second,NULL);
    pthread_create(&control,NULL,sum,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(control,NULL);
  }

  return 0;
}
