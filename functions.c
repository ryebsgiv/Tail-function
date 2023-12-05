/**
 * @file functions.c
 * @author Ben Givens
 * @brief function definition file
 * @date 2023-10-12
 */
#include "functions.h"
/**
 * @brief Reads the file into a char value and dynamically allocates it to a temp buffer.
 * 
 * @param numberOfLines number of possible lines
 * @param file name of file
 */
void readFile(int numberOfLines, int file, int startingPosistion)
{
    char buffer[1];//max char per line
    char *tempbuffer=NULL; //dynamically allocated array of char
    int readLines=0;//The number of lines read

    off_t offset = lseek(file, -1, SEEK_END);//go to end of file
    if (offset==-1)
    {
        perror("Something went wrong with seeking the EOF\n");
        return;
    }

    int totalNumber=0;//total number of char values
    while (readLines<numberOfLines)
    {
        read(file, buffer, sizeof(buffer));//read a char into buffer
        if (buffer[0]=='\n')//if its a newline then add to the readLines variable
        {
            readLines++;
            if (numberOfLines==readLines)
                break;
        }
        tempbuffer = (char *)realloc(tempbuffer,totalNumber+1); //allocate memory for additional char value
        tempbuffer[totalNumber]=buffer[0]; //add char to dynamic array
        totalNumber++;
        lseek(file,-1-totalNumber,SEEK_END);//go to the end of the file minus the total number 
    }
    char tempvalue[1];
    int startValue=1;
    for (int i=totalNumber-2; i>=0; i--)
    {
        if (tempbuffer[i]=='\n'){
            startValue++;
        }
    }
    startValue=startValue+startingPosistion;//The number of lines that it should skip in the buffer - the users entered start posistion
    for (int i=totalNumber-1; i>=0; i--)
    {   
        //if tempbuffer[i]=='\n' and the user inputed a unique start line posistion
        //then reduce the start value to not account for the lines the user didn't want included.
        if (tempbuffer[i]=='\n' && startingPosistion != -1)
        {
            startValue--;
            if (startValue==-1)
                break;
        }
        tempvalue[0]=tempbuffer[i];
        write (1, tempvalue, 1); //print the array backwards
    }
    tempvalue[0]='\n';
    write (1, tempvalue,1);
    free(tempbuffer);
}