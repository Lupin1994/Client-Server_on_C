#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList/LinkedList.h"

char** string_split(char *inputString, char separator, int *splittedCount){
    
    char **splittedString = (char**)malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; i++)
    {
        splittedString[i] = (char*)malloc(100 * sizeof(char));
    }
    
    TLinkedListItem *splittedPartString = linked_list_create();
    
    int splittedStringIndex = 0;
    int splittedPartStringIndex = 0;
    for (int inputStringIndex = 0; inputString[inputStringIndex] != '\0'; inputStringIndex++)
    {
        linked_list_add(splittedPartString, inputString[inputStringIndex]);

        if (inputString[inputStringIndex] == separator)
        {
            int splittedPartStringCount = linked_list_count_elements(splittedPartString);
            for (int k = 0; k < splittedPartStringCount - 1; k++) // Если 10 он записывает в одну строку два значения, почему???
            {
                splittedString[splittedStringIndex][k] = linked_list_get_element_by_index(splittedPartString, k);
                //printf("in split char : %c\n", linked_list_get_element_by_index(splittedPartString, k));
            } 

            splittedStringIndex++;
            splittedPartString = linked_list_remove_all(splittedPartString);
            //linked_list_print(splittedPartString);

        }
        
    }
    
    int splittedStringCount = linked_list_count_elements(splittedPartString);
    //printf("in split : %d\n", splittedStringCount);
    for (int i = 0; i < splittedStringCount; i++)
    {
        splittedString[splittedStringIndex][i] = linked_list_get_element_by_index(splittedPartString, i);
        //printf("index : %d", splittedStringIndex);
    }

    if (splittedCount != NULL)
    {
        *splittedCount = splittedStringIndex + 1; // Беру просто индекс
        printf("in split after: %d\n", *splittedCount);
    }

    return splittedString;
}

char* string_concat(char *string1, char *string2){
    
    size_t len1 = strlen(string1);
    size_t len2 = strlen(string2);                      

    char *result = malloc(len1 + len2 + 1);

    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, string1, len1);
    memcpy(result + len1, string2, len2 + 1);    

    return result;
}