/*
 * Group 3:
 * Siddharth Banerjee 002111001097
 * Tanmay Roy 002111001017
 * Anupam Ghosh 002111001102
 * Vikash Sangai 002111001100
 *
 * Date: 14/7/23 
 */

/*
 **Problem Definition :
*  Create two processes. Transfer 1GB file from process1 to process2 using a Socket.
*  Now, transfer that file from process2 to process1 using the same Socket.
*  Now, compare the two files to make sure that the same file has returned back.
*      
*  Also, print the time required to do this double transfer. Attach this output to 
*  the source file as a comment.
*
*  Please note that, you can see the socket which your program creates. There
*  are also various bash shell commands available to see the sockets created by
*  the program. So, once your program creates the socket, make sure you use
*  proper command to see the socket info and paste that output as a comment in
*  your source file.
* 
*/

/*
 *  truncate -s 1G input.txt
 *  gcc -Wall -g -o sock 03_03.c
 *  ./sock; diff -s input.txt /tmp/process1_receivedFile
 * */

/*
 * output:
 * Server side socket created successfully...
Socket bind to server suceessfully...
Server is listening on port: 8000
Client side socket created successfully...
Client connected to the server successfully
Server connected to the client successfully

---------------------------------------------
Time taken for Double Transfer: 2.805746 sec
---------------------------------------------
Files input.txt and /tmp/process1_receivedFile are identical
❯ ss -a -t
State                  Recv-Q              Send-Q                                                       Local Address:Port                                                               Peer Address:Port               Process
LISTEN                 0                   32                                                           192.168.122.1:domain                                                                  0.0.0.0:*
LISTEN                 0                   4096                                                         127.0.0.53%lo:domain                                                                  0.0.0.0:*
LISTEN                 0                   128                                                                0.0.0.0:ssh                                                                     0.0.0.0:*
LISTEN                 0                   5                                                                127.0.0.1:ipp                                                                     0.0.0.0:*
LISTEN                 0                   244                                                              127.0.0.1:postgresql                                                              0.0.0.0:*
LISTEN                 0                   244                                                              127.0.0.1:5433                                                                    0.0.0.0:*
LISTEN                 0                   4096                                                             127.0.0.1:9050                                                                    0.0.0.0:*
ESTAB                  0                   0                                                           192.168.29.178:47920                                                            44.238.139.194:https
ESTAB                  0                   0                                                           192.168.29.178:58522                                                             54.230.222.68:https
ESTAB                  0                   0                                                           192.168.29.178:38432                                                            172.217.167.46:https
ESTAB                  0                   0                                                           192.168.29.178:38444                                                             52.25.208.206:https
ESTAB                  0                   0                                                           192.168.29.178:40086                                                              34.117.65.55:https
ESTAB                  0                   0                                                           192.168.29.178:51142                                                            142.250.192.14:https
TIME-WAIT              0                   0                                                           192.168.29.178:60678                                                             142.250.195.3:https
TIME-WAIT              0                   0                                                                127.0.0.1:53960                                                                 127.0.0.1:8000
ESTAB                  0                   0                                                           192.168.29.178:58688                                                             52.13.205.177:https
ESTAB                  0                   0                                                           192.168.29.178:60408                                                            199.232.22.167:https
LISTEN                 0                   511                                                                      *:http                                                                          *:*
LISTEN                 0                   50                                                                       *:1716                                                                          *:*
LISTEN                 0                   128                                                                   [::]:ssh                                                                        [::]:*
LISTEN                 0                   5                                                                    [::1]:ipp                                                                        [::]:*
ESTAB                  0                   0                                 [2405:201:8008:e0fa:766c:b993:8896:b131]:38642                                       [2a03:2880:f26b:c9:face:b00c:0:167]:https
ESTAB                  0                   0                                 [2405:201:8008:e0fa:766c:b993:8896:b131]:53006                                       [2a03:2880:f26b:c9:face:b00c:0:167]:https
ESTAB                  0                   0                                 [2405:201:8008:e0fa:766c:b993:8896:b131]:53494                                  [2405:200:1630:ff97:face:b00c:3333:7020]:https
ESTAB                  0                   0                                 [2405:201:8008:e0fa:766c:b993:8896:b131]:32970                                                [2404:6800:4002:807::200d]:https
ESTAB                  0                   0                                 [2405:201:8008:e0fa:766c:b993:8896:b131]:58026                                      [2600:9000:253f:1a00:c:132:48e:f021]:https
 * */


#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

#define MAXLEN 1024               // max length of each buffer/packet
#define IP_ADDRESS "127.0.0.1"   // IP Address of the Localhost
#define PORT 8000               // Port Number

#define BUFFER_FILE1 "/tmp/process1_receivedFile"
#define BUFFER_FILE2 "/tmp/process2_receivedFile"


// find the file size (in bytes), it will help us to check whether the entire file has reached the other side or not
long getFileSize(char* filename) 
{
    FILE* file;

    // try to open the file
    if ((file = fopen(filename, "r")) == NULL) 
    {
        perror("Error: Unable to determine the file size (fopen error)\n");
        return -1;
    }

    // It takes the pointer to the EOF
    if (fseek(file, 0, SEEK_END) == -1) 
    {
        perror("Error: Unable to determine file size (fseek error)\n");
        return -1;
    }

    // It finds the size of the file, by calculating the difference between the start of the file & the current position of the pointer in the file
    long size = ftell(file);
    if (size == -1) 
    {
        perror("Error: Unable to determine file size (ftell error)\n");
        return -1;
    }

    return size;
}

// sending the file via the socket 
int sendFile(char *originalFile, int destination){

    // find the file size of the original file
    long fileSize = getFileSize(originalFile);

    if(fileSize == -1){     // error in getting the size of the file
        return -1;
    }
    
    // We can't transfer the whole file in a single run, we have to break the large file in small chunks(packets)
    char buffer[MAXLEN];    // 1st buffer/packet created

    *((long *)buffer) = fileSize;   // 1st packet will contain the size of the file
    // Reason behind sending the file size: In the other side, receiver can determine whether the entire file has been received or not

    if(send(destination, buffer, sizeof(long), 0) < 0){
        perror("Error: Unable to send the file\n");
        return -1;
    }

    // try to open the original file
    int file_id = open(originalFile, O_RDONLY);
    if(file_id == -1){
        perror("Error: Unable to open the file\n");
        return -1;
    }
    
    int returnValue = 1;

    // this loop will run until the entire file (divided in small packets) is sent
    while(true){

        // reading from the file into the buffer
        long bufferRead = read(file_id, buffer, MAXLEN);

        if(bufferRead < 0){
            perror("Error: Unable to read the file\n");
            returnValue = -1;
            break;
        }

        if(bufferRead == 0){
            break; // EOF reached
        }

        // try to send the buffer/packet to the other side of the socket
        if (send(destination, buffer, bufferRead, 0) == -1){
            returnValue = -1;
            break;
        }

    }

    // try to close the file
    if (close(file_id) == -1){
        perror("Error: Unable to close the file\n");
        return -1;
    }

    return returnValue;     // if the file has been sent successfully, it will return 1
}


//receiving the file via the socket
int receiveFile(char* destinationFile, int source){

    // try to store the size of the file
    char buffer[MAXLEN];

    // try to receive the file-size to check whether the entire file has been received or not
    if(recv(source, buffer, sizeof(long),0) < 0){
        perror("Error: Unable to receive the file\n");
        return -1;
    }

    // storing the size of the file
    long file_size = *((long *)buffer);

    // try to open the destination file, where the contents of every packets received via socket will be stored
    int destination_id = open(destinationFile,O_WRONLY | O_CREAT , 0666);

    if(destination_id < 0){
        perror("Error: Unable to open the destination file\n");
        return -1;
    }

    long temp_file_size = file_size;

    int returnValue = 1;

    // this loop willb run until the entire file has been received
    while(temp_file_size > 0){

        // receiving contents in form of packets
        int bytesRead = recv(source, buffer, MAXLEN,0);

        if(bytesRead < 0){
            perror("Error: Unable to read the packet\n");
            returnValue = -1;
            break;
        }

        if(bytesRead == 0){     // EOF reached
            break;
        }

        // try to write into the destination file
        if(write(destination_id, buffer, bytesRead) < 0){
            perror("Error: Unable to write into the destination file\n");
            returnValue = -1;
            break;
        }

        temp_file_size -= bytesRead;     // decrementing the size of the packet that has been received successfully
    }
    
    // try to close the file
    if(close(destination_id) < 0){
        perror("Error: Unable to close the destination file\n");
        return -1;
    }
    
    return returnValue;     // If the file has been received successfully, it will return 1
}

// creating the server
int createServer(){

    int server_id;

    server_id = socket(AF_INET,SOCK_STREAM, 0);
    if(server_id < 0){
        perror("Error: Unable to create server side socket\n");
        return server_id;
    }
    printf("Server side socket created successfully...\n");

    // server side address information
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;     // IPv4 family of addresses
    server_address.sin_port = htons(PORT);  // adding the port number
    server_address.sin_addr.s_addr = INADDR_ANY; 
    bzero(&server_address.sin_zero, 8);

    // try to bind the server address to the socket created
    if (bind(server_id, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error: Unable to bind socket to server\n");

        if (close(server_id) == -1) {
            perror("closing...\n");
        }

        return -1;
    }
    printf("Socket bind to server suceessfully...\n");

    // listening for the clients 
    if (listen(server_id,1) < 0){
        perror("Error: Unable to listen for clients\n");

        if (close(server_id) == -1) {
            perror("closing...\n");
        }

        return -1;
    }
    printf("Server is listening on port: %d\n", PORT);
    
    return server_id;   // it returns the server side descriptor
}

// try to connect the server to the client
int acceptConnection(int server_id){

    int connectionfd;                   // connection socket file descriptor
    struct sockaddr_in client_address; // a sockaddr_in for client
    unsigned int addrlen = sizeof(client_address);

    // try to accept the client and connecting to the server
    connectionfd = accept(server_id, (struct sockaddr*)&client_address, &addrlen);
    if (connectionfd < 0) 
    {
        perror("Error: Unable to accept connection from server\n");
        return -1;
    }

    return connectionfd;    // it returns the server side descriptor
}


// try to connect the client to the server
int connectToServer(){
    
    int client_id = socket(AF_INET, SOCK_STREAM, 0);
    if(client_id < 0){
        perror("Error: Unable to create client side socket\n");
        return client_id;
    }
    printf("Client side socket created successfully...\n");

    // client side address information
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;     // IPv4 address family
    client_address.sin_port = htons(PORT);  // adding port to the address
    client_address.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    bzero(&client_address.sin_zero, 8);   

    // try to connect with the server side of the socket
    if(connect(client_id, (struct sockaddr *)&client_address, sizeof(client_address)) < 0){
        perror("Error: Unable to connect client with the server\n");
        
        if (close(client_id) == -1) {
            perror("closing...\n");
        }
        return -1;
    }

    return client_id;   // It returns the client side descriptor
}

// process1 (server side)
void process1(char* source_file){

    // try to create a server socket
    int server_id = createServer(); 
    if(server_id < 0){
        perror("Error: createServer() failed\n");
        exit(EXIT_FAILURE);
    }

    int connect_id = acceptConnection(server_id);
    if(connect_id < 0){
        perror("Error: acceptConnection() failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Server connected to the client successfully\n");

    // process starts... call gettimeofday
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    if(sendFile(source_file, connect_id) < 0){
        if(close(connect_id) < 0){
            perror("closing...\n");
        }
        if(close(server_id) < 0){
            perror("closing...\n");
        }
        exit(EXIT_FAILURE);
    }

    if(receiveFile(BUFFER_FILE1,connect_id) < 0){
        if(close(connect_id) < 0){
            perror("closing...\n");
        }
        if(close(server_id) < 0){
            perror("closing...\n");
        }
        exit(EXIT_FAILURE);
    }

    // process ends... call gettimeofday
    gettimeofday(&endTime, NULL);

    double timeValue =  (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
    

    printf("\n\t---------------------------------------------\n");
    printf("\tTime taken for Double Transfer: %lf sec\n", timeValue);
    printf("\t---------------------------------------------\n");

    // try to close the connection to the socket
    if(close(connect_id) < 0){
        perror("Error: Unable to disconnect the socket\n");
    }

    if(close(server_id) < 0){
        perror("Error: Unable to disconnect the socket\n");
    }
}

// process2 (client side)
void process2(){

    int client_id = connectToServer();  // try to connect the client to the server
    if(client_id < 0) {
        perror("connectToServer failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Client connected to the server successfully\n");

    // try to receive the file via the socket (from the server)
    if (receiveFile(BUFFER_FILE2, client_id) == -1) 
    {
        if (close(client_id) < 0) {
            perror("closing...\n");
        }
        exit(EXIT_FAILURE);
    }

    // try to send the file via the socket (from the client)
    if (sendFile(BUFFER_FILE2, client_id) < 0 ) 
    {
        if (close(client_id) == -1) 
        {
            perror("closing...\n");
        }
        exit(EXIT_FAILURE);
    }
}


int main() {

    // path of the inputfile that is to be sent and received via the sockets
    char* inputFile = "input.txt";
    
    // forking to create two processes (parent and child)
    pid_t fork_id = fork();
    if(fork_id < 0){
        perror("Error: Unable to fork...\n");
        return 1;
    }
    
    else if(fork_id == 0){
        // child process (process2)
        process2();
    }
    else{
        // parent process (process1)
        process1(inputFile);
    }

    return 0;
}
