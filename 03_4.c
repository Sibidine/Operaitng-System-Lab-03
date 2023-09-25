 /* Group 3:
 * Siddharth Banerjee 002111001097
 * Tanmay Roy 002111001017
 * Anupam Ghosh 002111001102
 * Vikash Sangai 002111001100
 * Date: 21/08/23
*/
 
/*Question:
 * Objective of this programming assignment is to use mmap() call and observe page-
 * fault using the ‘sar’ command.
 * A big file (about 8GB) should be created using the ‘fallocate’ command. This big file
 * should be written with a single integer value (say X) at a specific offset (say F). Both
 * the integer value and the offset should be generated using a random function.
 * Please do remember this random function should generate a quantity anywhere
 * between 0 and 8G.
 * The above big file should also be mapped in the virtual address space using mmap()
 * call. Once it is mapped, the data should be read from the same specific offset (F).
 * Now, if the data read is X`; then verify that X and X` are the same. In case of verification failure, 
 * an error message is to be printed. Note that, the offset value F can be anywhere between 0 and 8G.
 * This sequence of writing and reading data to/from a specific offset and also
 * verification should be put in a while loop to go forever.
 * In another terminal execute the command ‘sar –B 1 1000’ to observe for the page
 * fault. This command should be started before the above program is put under
 * execution. So, one can observe that the page faults are increasing, once the above
 * program starts executing.
 * The output of the program and the ‘sar’ command should be pasted as a comment
 * at the beginning of the program file as indicated by the guidelines.
 * */

/* Compilation instructions:
 * fallocate -l 8G /tmp/Generated_File.txt
 * gcc -Wall -g -o pagef 03_4.c
 *./pagef
 * 
 * to find page faults: execute "sar -b 1" in a seperate terminal
 * */

/* output of the program:
The Value Written is : 313717581 
The Value Read is : 313717581 
The position in the file where a value is being written and read: 0x70ddcf7f
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1146823123
The Value Read is : 1146823123
The position in the file where a value is being written and read: 0x69bb7f1e
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1392337438
The Value Read is : 1392337438
The position in the file where a value is being written and read: 0x6512d0d4
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 481766202 
The Value Read is : 481766202 
The position in the file where a value is being written and read: 0x2ebd8517
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1466322816
The Value Read is : 1466322816
The position in the file where a value is being written and read: 0xba8394f
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1423075311
The Value Read is : 1423075311
The position in the file where a value is being written and read: 0x3e4a1b22
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 2464661   
The Value Read is : 2464661   
The position in the file where a value is being written and read: 0x697f474a
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1451942073
The Value Read is : 1451942073
The position in the file where a value is being written and read: 0x50b397e
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1704959977
The Value Read is : 1704959977
The position in the file where a value is being written and read: 0x4a3ce0ef
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1198904398
The Value Read is : 1198904398
The position in the file where a value is being written and read: 0x42b5b00
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 2045669234
The Value Read is : 2045669234
The position in the file where a value is being written and read: 0x11dcc400
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1628889217
The Value Read is : 1628889217
The position in the file where a value is being written and read: 0x374a80a8
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1775703675
The Value Read is : 1775703675
The position in the file where a value is being written and read: 0x6aaa2fee
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 367620740 
The Value Read is : 367620740 
The position in the file where a value is being written and read: 0x7b586dfd
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 1015244495
The Value Read is : 1015244495
The position in the file where a value is being written and read: 0x421aa89c
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 2055659972
The Value Read is : 2055659972
The position in the file where a value is being written and read: 0x4f365a1c
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 855144476 
The Value Read is : 855144476 
The position in the file where a value is being written and read: 0x3ee20397
The value that is read and written are the same!
---------------------------------------------
The Value Written is : 955373882 
The Value Read is : 955373882 
The position in the file where a value is being written and read: 0x5f5da3a
The value that is read and written are the same!
^C


* output of the sar command:
Linux 5.15.0-79-generic (HP-Pavillion)  26/08/23        _x86_64_        (8 CPU)

03:35:07 PM IST       tps      rtps      wtps      dtps   bread/s   bwrtn/s   bdscd/s
03:35:08 PM IST      0.00      0.00      0.00      0.00      0.00      0.00      0.00
03:35:09 PM IST      0.00      0.00      0.00      0.00      0.00      0.00      0.00
03:35:10 PM IST    547.00    547.00      0.00      0.00  28984.00      0.00      0.00
03:35:11 PM IST   8548.00   8548.00      0.00      0.00  69128.00      0.00      0.00
03:35:12 PM IST   8708.00   8706.00      2.00      0.00  69896.00     88.00      0.00
03:35:13 PM IST   9738.00   8716.00   1022.00      0.00  70144.00   8472.00      0.00
03:35:14 PM IST   8770.00   8770.00      0.00      0.00  70376.00      0.00      0.00
03:35:15 PM IST   8740.00   8740.00      0.00      0.00  70368.00      0.00      0.00
03:35:16 PM IST   8709.00   8709.00      0.00      0.00  69864.00      0.00      0.00
03:35:17 PM IST   8728.00   8727.00      1.00      0.00  70416.00     64.00      0.00
03:35:18 PM IST  34281.00   1826.00  32455.00      0.00  14776.00 295496.00      0.00
03:35:19 PM IST  23049.00     99.00  22950.00      0.00   1016.00 208624.00      0.00
03:35:20 PM IST      0.00      0.00      0.00      0.00      0.00      0.00      0.00
03:35:21 PM IST      0.00      0.00      0.00      0.00      0.00      0.00      0.00
^C
Average:      8558.43   4527.71   4030.71      0.00  38212.00  36624.57      0.00

 * */


// Header Files
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define LOWER 0          // LOWER bound for the bytes in the file
#define UPPER 8589934592 // UPPER bound for the bytes in the file (equal to 2^33 for the size of the 8 GB)
char *addressOfMapBuffer; // The address of the buffer created by the mmap() method call is stored

int readValueFromFile(unsigned long offset)
{
    unsigned long readValue;
    sscanf(addressOfMapBuffer + offset, "%lu", &readValue);
    printf("The Value Read is : %-10lu\n", readValue);
    return readValue;
}

void writeInteger(unsigned long offset, unsigned long value)
{
    printf("The Value Written is : %-10lu\n", value);
    sprintf(addressOfMapBuffer + offset, "%lu", value);
}

unsigned long randomNumberGenerator()
{
    unsigned long lowerRange = LOWER;
    unsigned long upperRange = UPPER;
    unsigned long randomNumber = lowerRange + (rand() % (upperRange - lowerRange + 1));
    return randomNumber;
}

char* ulongToHex(unsigned long num) {
    char* hexString = (char*)malloc(sizeof(char) * 12); // Maximum 8 hex digits + 2 "0x" + null terminator
    if (hexString == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    sprintf(hexString, "0x%lx", num);
    return hexString;
}

int main()
{

    // Opening the user specified file
    int FILE = open("/tmp/Generated_File.txt", O_RDWR, S_IRUSR | S_IWUSR);
    // The information about the user specified file is stored the stat structure
    struct stat sb;

    // Getting the information of the file in the sb variable
    if (fstat(FILE, &sb) == -1)
    {
        perror("Some ERROR occured while getting the file size!");
        exit(1);
    }

    // Mapping the file in the virtual address space using mmap()
    if ((addressOfMapBuffer = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, FILE, 0)) == MAP_FAILED)
    {
        perror("Some ERROR occured while mapping the file!");
        exit(1);
    }

    // Setting the seed value for the rand() function
    srand(time(NULL));
    unsigned long offset, writeValue, readValue;

    while (1)
    {
        writeValue = randomNumberGenerator();
        offset = randomNumberGenerator(); 
 
        writeInteger(offset, writeValue);
 
        readValue = readValueFromFile(offset);

	char* hexAddress = ulongToHex(offset);
        printf("The position in the file where a value is being written and read: %s\n",hexAddress);
        if (writeValue == readValue)
        {
            printf("The value that is read and written are the same!\n");
            printf("---------------------------------------------\n");
	}
	else
        {
            printf("The value that is read and written are NOT the same!\n");
            printf("---------------------------------------------\n");
        }
    }

    return 0;
}
