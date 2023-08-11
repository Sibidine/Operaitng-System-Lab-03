/*
 * Group 3:
 * Siddharth Banerjee 002111001097
 * Tanmay Roy 002111001017
 * Anupam Ghosh 002111001102
 * Vikash Sangai 002111001100
 * Date: 07/08/23
 */

/*
 * Catch the signal ‘SIGINT’ and display “Ha Ha, Not Stopping”. Use ‘signal’system call.
 */

/*
 * gcc -Wall -g -o interrupt 03_2A.c
 * ./interrupt
 */

/*
 * input: N/A
 * output:
^C
        Ha Ha, not stopping...
^C
        Ha Ha, not stopping...
^C
        Ha Ha, not stopping...
^C
        Ha Ha, not stopping...
^C
        Ha Ha, not stopping...



 * */

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void signal_handler(int signo)
{
    if(signo == SIGINT)
        printf("\n\tHa Ha, not stopping...\n");
    
}

int main()
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        perror("couldn't catch SIGINT");

    // the infinite loop 
    while(1)
    {
    }
    return 0;
}
