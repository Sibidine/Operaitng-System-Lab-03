
 /* Group 3:
 * Siddharth Banerjee 002111001097
 * Tanmay Roy 002111001017
 * Anupam Ghosh 002111001102
 * Vikash Sangai 002111001100
 * Date: 11/09/23
*/

 /*
  * Consider a main process which creates three threads Th1, Th2, and Th3. The main
process also creates two random quantities (X, Y), both less than 10. These two
values will be placed by the main process in the shared memory (One variant of IPC
Primitive) that is accessible by all the three threads Th1, Th2 and Th3. The shared
memory will be created by the main process also.
For each pair of values (X,Y), it is required that some computations will be done by
various threads. The thread Th1 will compute A (X*Y) and the thread Th2 will
compute B (X*Y)/2). Similarly, Th3 computes C (X+Y), Th2 again computes D
((X*Y)/(X+Y)), and finally Th1 computes E ((X+Y)(X-Y)). All these values are kept in
the shared memory in a tabular fashion as shown below.
The number of (X,Y) pairs will be taken as an argument from the CLI. It is the
responsibility of the main process to populate required numbers of (X,Y)s in the
shared memory. The program will only exit when all A,B,C etc. are computed for all
given (X,Y) values. Before exiting, all (X,Y)s, As, Bs etc. should be displayed.
Whenever, the threads complete one phase of computations (A, B, C, D and E), they
will go for another pair of (X,Y) values; but they will start all together. This can be
achieved by proper synchronization.
Use the proper shell command to display the Shared Memory Status/Info/Statistics
and attach this sample output as a comment.
  * */

 /*
  * Compilation instructions:
  * gcc -Wall -g -o ipc 03_7.c -lpthread
  * execution:
  *
  * ./ipc {number of iterations}
 */

/*Input: number of threads = 5
 * ./ipc 5
Pairs(X,Y)|     A       |       B       |       C       |       D       |       E
___________________________________________________________________________________________
(7,7)   |       49      |       24      |       3       |       14      |       0
___________________________________________________________________________________________
(5,6)   |       30      |       15      |       2       |       11      |       -11
___________________________________________________________________________________________
(3,8)   |       24      |       12      |       2       |       11      |       -2
___________________________________________________________________________________________
(1,4)   |       4       |       2       |       0       |       5       |       -1
___________________________________________________________________________________________
(5,2)   |       10      |       5       |       1       |       7       |       2
___________________________________________________________________________________________
Output of 'ipcs -m' during program execution:

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x00010f2c 45449222   siddharth  666        4          0                       
0x00003039 45449223   siddharth  666        28         1                       
0x00000000 11         siddharth  600        524288     2          dest         
0x00000000 54460429   siddharth  600        163840     2          dest         
0x00000000 54460430   siddharth  600        163840     2          dest         
0x00000000 15         siddharth  600        67108864   2          dest         
0x00000000 2261012    siddharth  600        524288     2          dest         
0x00000000 327707     siddharth  600        524288     2          dest         
0x00000000 54657054   siddharth  600        61440      2          dest         
0x00000000 54657055   siddharth  600        61440      2          dest         
0x00000000 54427680   siddharth  600        241664     2          dest         
0x00000000 8519713    siddharth  600        524288     2          dest         
0x00000000 54427682   siddharth  600        241664     2          dest         
0x00000000 55148581   siddharth  600        73728      2          dest         
0x00000000 55148582   siddharth  600        73728      2          dest         
0x00000000 54853672   siddharth  600        40960      2          dest         
0x011c00a6 54329385   postgres   600        56         6                       
0x0052e2c1 54329386   postgres   600        56         6                       
0x00000000 54853675   siddharth  600        40960      2          dest         
0x00000000 45416495   siddharth  600        393216     2          dest         
0x00000000 45416496   siddharth  600        2097152    2          dest         
0x010a0034 54329393   postgres   600        56         6                       
0x00000000 54493235   siddharth  600        126976     2          dest         
0x00000000 54493236   siddharth  600        126976     2          dest         
0x00000000 54984757   siddharth  600        32768      2          dest         
0x00000000 54984758   siddharth  600        32768      2          dest         
0x00000000 47284280   siddharth  600        2097152    2          dest         
0x00000000 6357049    siddharth  600        524288     2          dest         
0x00000000 47284282   siddharth  600        393216     2          dest         
0x00000000 2261055    siddharth  600        4194304    2          dest      
 * */

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define SHARED_MEMORY_KEY 12345

pthread_mutex_t mutex1;

int* X;

void displayIPCSharedMemory() {
    char command[] = "ipcs -m";
    char buffer[128];
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        perror("popen");
        exit(1);
    }

    printf("Output of 'ipcs -m' during program execution:\n");

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }

    pclose(pipe);
}

int randomNumberGenerator(int lowerCap, int higherCap)		
{
    int difference = higherCap - lowerCap;
    int randomNumber = lowerCap + rand()%(difference + 1);
    return randomNumber;
}


void createSharedMemory() 
{
    int shmid;

    // Create or get the shared memory segment
    shmid = shmget(SHARED_MEMORY_KEY, sizeof(int)*7, 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory
    X = (int *)shmat(shmid, NULL, 0);

    if (*X == -1) {
        perror("shmat");
        exit(1);
    }
    X[0] = randomNumberGenerator(1, 9);
    X[1] = randomNumberGenerator(1,9);
    X[2] = 0;
    X[3] = 0;
    X[4] = 0;
    X[5] = 0;
    X[6] = 0;

}

void* Th1()
{
    pthread_mutex_lock(&mutex1);
    X[2] = (X[0]*X[1]);
    if(!(X[0] == X[1]))
    X[6] = (int)((X[0]+X[1])/(X[0]-X[1]));
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void* Th2()
{
 
    pthread_mutex_lock(&mutex1);
    X[3] = (int)(X[0]*X[1])/2;
    X[4] = (int)(X[0]*X[1])/(X[0]+X[1]);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void* Th3()
{

    pthread_mutex_lock(&mutex1);
    X[5] = X[0]+X[1];
    pthread_mutex_unlock(&mutex1);
    return NULL;
}


int main(int argc, char* argv[])
{

    printf("Pairs(X,Y)|\tA\t|\tB\t|\tC\t|\tD\t|\tE\n");
    printf("___________________________________________________________________________________________\n");
    pthread_mutex_init(&mutex1,NULL);

    srand((unsigned) time(0));
    pthread_t th1,th2,th3;
    int inputs = atoi(argv[1]);
    for(int i = 0;i<inputs;i++)
    {
        createSharedMemory();
        printf("(%d,%d)\t|\t",X[0],X[1]);
        pthread_create(&th1,NULL,Th1,NULL);
        pthread_create(&th2,NULL,Th2,NULL);
        pthread_create(&th3,NULL,Th3,NULL);
        pthread_join(th1,NULL);  
        pthread_join(th2,NULL);  
        pthread_join(th3,NULL);
        printf("%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n",X[2],X[3],X[4],X[5],X[6]);
        printf("___________________________________________________________________________________________");
        printf("\n");
        if(i == inputs-1)
            displayIPCSharedMemory();
        shmdt(X);
    }
    return 0;
}
