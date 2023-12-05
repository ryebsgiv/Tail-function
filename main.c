/**
 * @file main.c
 * @author Ben Givens
 * @brief Created a tail function using system calls
 * @date 2023-10-12
 */
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "functions.h"
int main(int argc, char *argv[])
{
    if (argc<2)
    {
        perror("Not enough files called\n");
        return 1;
    }

    int numOfLines=10;//base value for number of lines
    int startingPosistion=-1;
    if (argc==2)
    {
        int file=open(argv[1],O_RDONLY);
        readFile(numOfLines, file,startingPosistion);
        close(file);
    }
    else if(strcmp(argv[1], "-n")==0)
    {

        if (argv[2][0]=='+')
        {
            startingPosistion-=atoi(argv[2]+1);
        }
        else
        {
            numOfLines=atoi(argv[2]);
        }
        int file=open(argv[3],O_RDONLY);
        readFile(numOfLines, file,startingPosistion);
        close(file);
    }
    else{
        perror("Something went wrong\n");
        return 1;
    }   
}