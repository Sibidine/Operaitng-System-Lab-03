 /* Group 3:
 * Siddharth Banerjee 002111001097
 * Tanmay Roy 002111001017
 * Anupam Ghosh 002111001102
 * Vikash Sangai 002111001100
 * Date: 04/09/23
*/
 
/*
 * You are supposed to write a C program which should print the following values on
terminal
Processor Informations (Vendor ID, Model Name and Cache Size in MB)
 Kernel Name, Kernel Release and Operating System Name.
 The amount of memory configured into this computer and Free Memory
 Amount of time since the system was last booted (In Hours, Minutes,
Seconds)
 * */

/*
 * Compilation instructions:
 * gcc -Wall -g -o procinfo 03_6.c
 * ./procinfo
 * */

/*
 * Output:
Processor Information:
Vendor ID: GenuineIntel
Model Name: 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
Cache Size: 8192 KB kB

Kernel Name: Linux
Kernel Release: 5.15.0-79-generic
Operating System Name: Linux version 5.15.0-79-generic (buildd@lcy02-amd64-014) (gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0, GNU ld (GNU Binutils for Ubuntu) 2.34) #86~20.04.2-Ubuntu SMP Mon Jul 17 23:27:17 UTC 2023

Total Memory: MemTotal:       16133084 kB
Free Memory: MemFree:         4508512 kB

Uptime: 420 hours, 42 minutes, 31 seconds

 * */

/*
 * The files used here are:
 *
 *  /proc/cpuinfo
    /proc/sys/kernel/ostype
    /proc/sys/kernel/osrelease
    /proc/version
    /proc/uptime
    /proc/meminfo
    
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>


#define BUFFER_SIZE 1024

int main() 
 {
    FILE* fp;
  	char buffer[BUFFER_SIZE];	// Buffer to store cpuinfo data line by line
	  size_t bytesRead;	// Number of bytes read in a line
	  char* match;		// Used for matching specific fields

    fp = fopen("/proc/cpuinfo", "rb");
	  bytesRead = fread(buffer, 1, sizeof(buffer), fp);
	  fclose(fp);

	  if(bytesRead==0)
    {
        perror("Error reading the file!\n");
        return 1;
      }

    // Processor Information

    // Ending the buffer with null character
    buffer[bytesRead] = '\0';

    match = strstr(buffer, "vendor_id");
    if(match==NULL)
    {
        perror("Vendor ID Not Found!\n");
        return 1;
    }
    char* vendorID = (char*)malloc(1024);
    sscanf(match, "vendor_id : %[^\n]", vendorID);

    match = strstr(buffer, "model name");
    if(match==NULL)
    {
        perror("Model Name Not Found!\n");
        return 1;
    }
    char* modelName = (char*)malloc(1024);
    sscanf(match, "model name : %[^\n]", modelName);

    match = strstr(buffer, "cache size");
    if(match==NULL)
    {
        perror("Cache Size not Found!\n");
        return 1;
    }
    char* cacheSize = (char*) malloc(1024);
    sscanf(match, "cache size : %[^\n]", cacheSize);

    float cache = atof(cacheSize);
    cache /= 1024;
    struct utsname uname_data;
    if (uname(&uname_data) != 0)
    {
        perror("Error retrieving system information");
        return 1;
    }  


    // Print the collected information
    printf("Processor Information:\n");
    printf("Vendor ID: %s\n", vendorID);
    printf("Model Name: %s\n", modelName);
    printf("Cache Size: %s kB\n\n", cacheSize);

    
    FILE *file;

    // Kernel Name
    file = fopen("/proc/sys/kernel/ostype", "r");
    if (file == NULL) 
    {
        perror("Failed to open /proc/sys/kernel/ostype");
        return 1;
    }
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    printf("Kernel Name: %s", buffer);

    // Kernel Release
    file = fopen("/proc/sys/kernel/osrelease", "r");
    if (file == NULL) 
    {
        perror("Failed to open /proc/sys/kernel/osrelease");
        return 1;
    }
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    printf("Kernel Release: %s", buffer);

    // Operating System Name
    file = fopen("/proc/version", "r");
    if (file == NULL) 
    {
        perror("Failed to open /proc/version");
        return 1;
    }
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    printf("Operating System Name: %s", buffer);


    printf("\n");
       // Open /proc/meminfo file
    file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Failed to open /proc/meminfo");
        return 1;
    }

    // Read and display total memory and free memory information
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        if (strstr(buffer, "MemTotal:") != NULL) 
        {
            printf("Total Memory: %s", buffer);
        }
        else if (strstr(buffer, "MemFree:") != NULL) 
        {
            printf("Free Memory: %s", buffer);
        }
    }

    fclose(file);

    printf("\n");

    double uptime_seconds;
    int hours, minutes, seconds;

    // Open /proc/uptime file
    file = fopen("/proc/uptime", "r");
    if (file == NULL) 
    {
        perror("Failed to open /proc/uptime");
        return 1;
    }

    // Read uptime in seconds
    if (fscanf(file, "%lf", &uptime_seconds) != 1) 
    {
        perror("Failed to read uptime from /proc/uptime");
        fclose(file);
        return 1;
    }

    fclose(file);

    // Convert uptime to hours, minutes, and seconds
    hours = (int)(uptime_seconds / 3600);
    minutes = (int)((uptime_seconds - (hours * 3600)) / 60);
    seconds = (int)(uptime_seconds - (hours * 3600) - (minutes * 60));

    // Display the uptime
    printf("Uptime: %d hours, %d minutes, %d seconds\n", hours, minutes, seconds);
    return 0;
}

