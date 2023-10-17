#include <stdio.h>

void string_split(char *inputString, char separator){

    char splittedString[10][10];
    char splittedPartString[10];
    
    int splittedStringIndex = 0;
    int splittedPartStringIndex = 0;
    for (int inputStringIndex = 0; inputString[inputStringIndex] != '\0'; inputStringIndex++)
    {
        
        splittedPartString[splittedPartStringIndex] = inputString[inputStringIndex];
        splittedPartStringIndex++;

        if (inputString[inputStringIndex] == separator)
        {
            for (int k = 0; k < 10; k++)
            {
                splittedString[splittedStringIndex][k] = splittedPartString[k];
                //printf("%s\n", splittedPartString);
            } 

            splittedStringIndex++;

            for (int i = 0; i < 10; i++)
            {
                splittedPartString[i] = ' ';
            }
            splittedPartStringIndex = 0;

        }
        //splittedPartStringIndex++;
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%s\n",splittedString[i]);

        // for (int j = 0; j < 10; i++)
        // {
        //     printf("(%s) , (%s)",splittedString[i][j]);
        // }
        
    }

    //return splittedString;
}