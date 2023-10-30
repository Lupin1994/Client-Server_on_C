#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList/LinkedList.h"

char** string_split(char *inputString, char separator){
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
            for (int k = 0; k < linked_list_count_elements(splittedPartString) - 1; k++) // Если 10 он записывает в одну строку два значения, почему???
            {
                splittedString[splittedStringIndex][k] = linked_list_get_element_by_index(splittedPartString, k);
            } 

            splittedStringIndex++;
            splittedPartString = linked_list_remove_all(splittedPartString);

        }
        
    }
    for (int i = 0; i < linked_list_count_elements(splittedPartString); i++)
    {
        splittedString[splittedStringIndex][i] = linked_list_get_element_by_index(splittedPartString, i);
    }
    return splittedString;
}

char* concat(char *string1, char *string2){
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