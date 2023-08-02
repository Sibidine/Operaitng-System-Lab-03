/*
 * Group 3:
 * Siddharth Banerjee 002111001097
 * Tanmay Roy 002111001017
 * Anupam Ghosh 002111001102
 * Vikash Sangai 002111001100
 * Date: 31/7/23
 */

/*
 * Display the following  environment variables using getenv call:
 * USER (your login name) 
 * HOME (the path name of your home directory) 
 * HOST (the name of the computer you are using) 
 * ARCH (the architecture of the computer's processor) 
 * DISPLAY (the name of the computer screen to display X windows) 
 * PRINTER (the default printer to send print jobs) 
 * PATH (the directories the shell should search to find a command)
 *Set two new environment variables and disp[lay them.
 */

/*
 * gcc -Wall -g -o EVM 03_1B.c
 * ./EVM
 */

/*
USER: siddharth
HOME: /home/siddharth
HOST: (null)
ARCH: (null)
DISPLAY: :0
PRINTER: (null)
PATH: /home/siddharth/.nvm/versions/node/v16.14.0/bin:/home/siddharth/.cargo/bin:/home/siddharth/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/siddharth/.dotnet/tools:/usr/local/go/bin:/usr/local/go/bin
New environment variable set successfully.
NEW_VARIABLE: Group 3 Environment Variable

*/

#include <stdio.h>
#include <stdlib.h>

int main() 
{
    char* user = getenv("USER");
    char* home = getenv("HOME");
    char* host = getenv("HOST");
    char* arch = getenv("ARCH");
    char* display = getenv("DISPLAY");
    char* printer = getenv("PRINTER");
    char* path = getenv("PATH");

    printf("USER: %s\n", user);
    printf("HOME: %s\n", home);
    printf("HOST: %s\n", host);
    printf("ARCH: %s\n", arch);
    printf("DISPLAY: %s\n", display);
    printf("PRINTER: %s\n", printer);
    printf("PATH: %s\n", path);

    char* newVariableName = "NEW_VARIABLE";
    char* newVariableValue = "Group 3 Environment Variable";
    if (setenv(newVariableName, newVariableValue, 1) == 0) 
    {
        printf("New environment variable set successfully.\n");
    } 
    else  
    {
	perror("Error, could not set environment variable, ");
	return(-1);
    }

    char* newVariable = getenv(newVariableName);
    printf("%s: %s\n", newVariableName, newVariable);

    return 0;
}
