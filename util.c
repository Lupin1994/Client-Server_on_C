#include <stdio.h>
#include "LinkedList/LinkedList.h"

void string_split(char *inputString, char separator){
    char splittedString[100][100];
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
    
    for (int i = 0; i < 10; i++)
    {
        printf("%s\n",splittedString[i]);
    }

    //return splittedString;
}