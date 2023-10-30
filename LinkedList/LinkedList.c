#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"

void linked_list_print(TLinkedListItem *head){
    if (head == NULL)
    {
        printf("Null !");
        return;
    }
    
    TLinkedListItem *list_writer;
    list_writer = head;
    printf("[");
    do
    {
        printf("%c ", list_writer->value);
        list_writer = list_writer->next_item;
    } while (list_writer != NULL);
    printf("]\n");
}

TLinkedListItem* linked_list_create(){
    TLinkedListItem *head = (TLinkedListItem*) malloc(sizeof(TLinkedListItem));
    head->value = 0;
    head->next_item = NULL;
    return head;
}

char linked_list_get_element_by_index(TLinkedListItem *head, int index){
    
    TLinkedListItem *current_item = head; 
    // printf("0\n");
    int current_item_index = 0;

    while (current_item != NULL)
    {
        //printf("1\n");
        if (current_item_index == index)
        {
            //printf("2\n");
            return current_item->value;
        }

        current_item_index++;
        current_item = current_item->next_item;
        //printf("3\n");
    }
    //printf("4");
    return 0;
}

void linked_list_add(TLinkedListItem * head, char value){
    if (head->value == 0)
    {
        head->value = value;
        head->next_item = NULL;
        return;
    }

    TLinkedListItem *new_item = (TLinkedListItem*) malloc(sizeof(TLinkedListItem));
    new_item->value = value;
    new_item->next_item = NULL;

    TLinkedListItem *current_item = head;
    while (current_item->next_item != NULL)
    {
        current_item = current_item->next_item;
    }
    current_item->next_item = new_item;
}
TLinkedListItem* linked_list_with_filtering_elements(TLinkedListItem *head, bool (*predicate)(char)){

    TLinkedListItem *linked_list_output = linked_list_create();
    TLinkedListItem *current_item = head;

    while (current_item != NULL)
    {
        if (predicate(current_item->value) == true)
        {
            linked_list_add(linked_list_output, current_item->value);
        }
        current_item = current_item->next_item;
    }
    return linked_list_output;
    
}

TLinkedListItem* linked_list_remove_by_index(TLinkedListItem* head, int index){

    if (head == NULL)
    {
        return NULL;
    }
    
    if (index == 0)
    {
        TLinkedListItem *second_item = head->next_item;
        free(head);
        if (second_item == NULL)
        {
            return linked_list_create();
        }

        return second_item;
    }

    TLinkedListItem *before_remove_item = head;
    
    int count = 0;
    while (count < index - 1)
    {
        if (before_remove_item->next_item == NULL)
        {
            return head;
        }

        before_remove_item = before_remove_item->next_item;
        count++;
    }

    TLinkedListItem *remove_item = before_remove_item->next_item;
    before_remove_item->next_item = before_remove_item->next_item->next_item;

    free(remove_item);
    return head;    
} 

TLinkedListItem* linked_list_add_element_by_index(TLinkedListItem *head, int index , char value){

    if (index == 0)
    {
        TLinkedListItem *new_head = linked_list_create();
        new_head->value = value;
        new_head->next_item = head;
        return new_head;
    }

    int count = 1;

    TLinkedListItem *current_item = head->next_item;
    while (count < index - 1)
    { 
        current_item = current_item->next_item;
        if (current_item == NULL)
        {
            printf("Index out of range! ");
            return head; 
        }
        count++;  
    }
    TLinkedListItem *before_index_item = current_item;

    TLinkedListItem *new_node = linked_list_create();
    new_node->value = value;
    new_node->next_item = before_index_item->next_item;

    before_index_item->next_item = new_node;

    return head;
}


int linked_list_count_elements(TLinkedListItem *head){
    int count = 0;

    while (head != NULL)
    {
        count++;
        head = head->next_item;
    }
    return count;
    
}

int linked_list_search_element(TLinkedListItem *head, char element, bool (*predicate)(char, char)){
    int count = 0;
    TLinkedListItem *current_item = head;
    while (current_item != NULL)
    {
        if (predicate(element, current_item->value) == true)
        {
            count++;
        }
        
        current_item = current_item->next_item;
    }
    return count;
    
}

TLinkedListItem* map(TLinkedListItem *head, char (function(char))){
    TLinkedListItem *list_output = linked_list_create();
    TLinkedListItem *current_item = head;
    while (current_item != NULL)
    {
        linked_list_add(list_output, function(current_item->value));
        current_item = current_item->next_item;
    }
    
    return list_output;
}

TLinkedListItem* linked_list_reverse (TLinkedListItem *head){
    TLinkedListItem *reverse_linked_list = NULL;

    while (head)
    {
        TLinkedListItem *next = head->next_item;
        head->next_item = reverse_linked_list;
        reverse_linked_list = head;
        head = next;
    }
    return reverse_linked_list;
}

TLinkedListItem* linked_list_remove_all(TLinkedListItem *head){

    int count_elements = linked_list_count_elements(head);
    TLinkedListItem* new_head = head;
    for (int i = 0; i < count_elements; i++)
    {
        new_head = linked_list_remove_by_index(new_head, 0);
    }

    return new_head;
}