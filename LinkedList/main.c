#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"

int main()
{
    TLinkedListItem *new_list = linked_list_create();
    TLinkedListItem *LinkedList_after_remove_all;

    linked_list_add(new_list, 'a');
    linked_list_add(new_list, 'b');
    linked_list_add(new_list, 'c');
    linked_list_add(new_list, 'd');
    linked_list_add(new_list, 'e');

    linked_list_print(new_list);
    char search_element = linked_list_get_element_by_index(new_list, 2);
    //printf("'%c'\n", search_element);
    // int count_elements = linked_list_count_elements(new_list);
    // printf("%d\n", count_elements);
    LinkedList_after_remove_all = linked_list_remove_all(new_list);
    linked_list_print(LinkedList_after_remove_all);
    // linked_list_add(LinkedList_after_remove_all, 'c');
    // linked_list_add(LinkedList_after_remove_all, 'd');
    // linked_list_add(LinkedList_after_remove_all, 'd');
    // linked_list_print(LinkedList_after_remove_all);
    

}