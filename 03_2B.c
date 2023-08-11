/*
 * Group 3:
 * Siddharth Banerjee 002111001097
 * Tanmay Roy 002111001017
 * Anupam Ghosh 002111001102
 * Vikash Sangai 002111001100
 * Date: 07/08/23
 */

/*
 *Create two processes. Transfer 1GB file from process1 to process2 using a
 FIFO. Now, transfer the same file from process2 to process1 using another 
 FIFO. Now, compare the two files to make sure that the same file has returned
 back. Also, print the time required to do this double transfer.
 */

/*
 * gcc -Wall -g -o fifo 03_2B.c
 * fallocate -l 1G /tmp/initialFile.txt
 * ./fifo
 */

/*
 * input: none
 * output:
❯ ./fifo
         Opened /tmp/initialFile.txt for reading

         Writing to fifo1

        Opened /tmp/receivedfile.txt for writing

         Reading from fifo1

         Writing to fifo1 is completed

read: No such file or directory
         Both the files are same, there is no mismatch!

         The round-about time for transferring the file between process1 and process2 and back to process1 is 1445 milliseconds

         File received from process 1

❯ ls -l /tmp
total 1048644
-rw------- 1 siddharth          0 Jul 18 19:32 config-err-Yb9zOp
prw-rw-r-- 1 siddharth          0 Aug  7 13:37 fifo1
drwxr-xr-x 2 root            4096 Aug  1 00:34 hsperfdata_root
drwxr-xr-x 2 siddharth       4096 Aug  5 01:09 hsperfdata_siddharth
-rw-rw-r-- 1 siddharth 1073741824 Aug  7 13:52 initialFile.txt
drwxrwxr-x 4 siddharth       4096 Aug  6 13:27 mintreport
drwxrwxrwx 2 siddharth       4096 Jul 18 19:32 mintUpdate
-rw-rw-r-- 1 siddharth          0 Aug  7 11:04 MozillaUpdateLock-4F96D1932A9F858E
-rw-rw-r-- 1 siddharth          0 Aug  7 13:52 receivedfile.txt
drwx------ 2 siddharth       4096 Jul 18 19:32 ssh-9m5wZvTPytOr
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-apache2.service-2I8JAg
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-colord.service-o8RzJg
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-ModemManager.service-x7Lbii
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-switcheroo-control.service-9xHp0f
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-systemd-logind.service-t9Fgaj
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-systemd-resolved.service-0ePiwg
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-systemd-timesyncd.service-ZSHHvh
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-tor@default.service-dvlCAh
drwx------ 3 root            4096 Jul 18 19:31 systemd-private-42d9d70a5a0d4111bd6c50054923761e-upower.service-CPfzRh
drwx------ 2 siddharth       4096 Aug  7 11:05 Temp-543d7ffc-fac4-4cbd-89a4-b900801156f1
drwx------ 2 siddharth       4096 Aug  7 12:24 vEGSant
 * */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

// Method to get the time elapsed since the invoking of this function
long getTimeElapsed()
{
    struct timeval timeElapsed;
    gettimeofday(&timeElapsed, NULL);
    return timeElapsed.tv_sec * 1000 + timeElapsed.tv_usec / 1000;
}


void compareFiles(FILE *firstFile, FILE *secondFile)
{
    char firstFileChar = getc(firstFile);
    char secondFileChar = getc(secondFile);

    int lineNumber = 1;
    int totalErrors = 0;

    while (firstFileChar != EOF && secondFileChar != EOF)
    {
        if (firstFileChar == '\n' && secondFileChar == '\n')
        {
            lineNumber++;
        }
        if (firstFileChar != secondFileChar)
        {
            totalErrors++;
            printf("\t Mismatch occurred at line number : %d\n\n", lineNumber);
        }

        firstFileChar = getc(firstFile);
        secondFileChar = getc(secondFile);
    }

    if (totalErrors == 0)
    {
        printf("\t Both the files are same, there is no mismatch!\n\n");
    }
}

int main()
{
    int startingTime = getTimeElapsed();
    char* fifo1 = "/tmp/fifo1";
    char* fifo2 = "/temp/fifo2";
    
    //mkfifo takes pathname,permission
    mkfifo(fifo1, 0666);
    mkfifo(fifo2,0666);

    int process2 = fork();

    if (process2 == 0) // Child process
    {
        // Reading from FIFO, writing into a file and sending to parent process
        // the file is generated in the /tmp directory due to it being used to store the short-lived temporary files 
        int fd = open(fifo1, O_RDONLY);
        const char *receivedFile = "/tmp/receivedfile.txt";
        FILE *receivedfp = fopen(receivedFile, "w");
        
        if (receivedfp == NULL)
            printf("\t Failed to open %s for writing\n\n", receivedFile);
        else
            printf("\tOpened %s for writing\n\n", receivedFile);
        
        if (fd > 0)
        {
            printf("\t Reading from fifo1\n\n");
            char str[100];
            while (read(fd, str, sizeof(str)))
            {
                fputs(str, receivedfp);
            }
            printf("\t File received from process 1\n\n");
            close(fd);
        }
        else
        {
            printf("\t Failed to open fifo1 for reading\n\n");
        }
        
        fclose(receivedfp);

    }

    else // Parent process
    {
        const char *initialFile = "/tmp/initialFile.txt";
        FILE *fp = fopen(initialFile, "r");
        if (fp == NULL)
            printf("\t Failed to open  %s for reading\n\n", initialFile);
        else
            printf("\t Opened %s for reading\n\n", initialFile);
        
        int fd = open(fifo1, O_WRONLY);
        
        if (fd > 0)
        {
            printf("\t Writing to fifo1\n\n");
            char str[100];
            while (fgets(str, sizeof(str), fp))
            {
                int len = strlen(str);
                int n = write(fd, str, len); // Writing to FIFO fifo1 from file initialFile.txt
                if (n != len)
                    perror("write");
            }

            printf("\t Writing to fifo1 is completed\n\n");
        }
        else
        {
            printf("\t Failed to open fifo1 for writing\n\n");
        }
        close(fd);
        fclose(fp);

        // Reading from fifo2 to check if file received back is same as file sent to process 2
        fd = open(fifo2, O_RDONLY);
        const char *receivedBackFile = "receivedBackFile.txt";
        FILE *receivedbackfp = fopen(receivedBackFile, "w");
        
        if (fd > 0)
        {
            printf("\t Reading from fifo2 and writing to %s to compare received back file with the initial file sent by process1\n\n", receivedBackFile);
            char buffer[100];
            while (read(fd, buffer, sizeof(buffer))) // Reading from fifo2 and writing to file receivedBackFile
            {
                fputs(buffer, receivedbackfp);
            }
        }
        else
        {
            perror("read");
        }

        close(fd);
        fclose(receivedbackfp);

        int endingTime = getTimeElapsed();
        int totalTimeTaken = endingTime - startingTime;

        // Comparing receivedBackFile.txt with initialFfile.txt
        fp = fopen(initialFile, "r");
        receivedbackfp = fopen(receivedBackFile, "r");
        compareFiles(fp, receivedbackfp);

        fclose(fp);
        fclose(receivedbackfp);
        printf("\t The round-about time for transferring the file between process1 and process2 and back to process1 is %d milliseconds\n\n", totalTimeTaken);
    }


    return 0;
}
