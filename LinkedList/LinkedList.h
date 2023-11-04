#include <stdbool.h>

typedef struct LinkedListItem TLinkedListItem;

struct LinkedListItem
{
    char value;
    TLinkedListItem *next_item;
};

bool predicate_filter_more_5(char element);
bool predicate_filter_even_number(char element);
bool predicate_search_equal_element(char search_element, char element_in_list);
char Map_transform_element(char element);

void linked_list_print(TLinkedListItem *head);
TLinkedListItem* linked_list_create();
char linked_list_get_element_by_index(TLinkedListItem *head, int index);
void linked_list_add(TLinkedListItem * head, char value);
TLinkedListItem* linked_list_remove_by_index(TLinkedListItem* head, int index);
TLinkedListItem* linked_list_with_filtering_elements(TLinkedListItem *head, bool (*predicate)(char));
TLinkedListItem* map(TLinkedListItem *head, char (function(char)));
int linked_list_search_element(TLinkedListItem *head, char element, bool (*predicate)(char, char));
TLinkedListItem* linked_list_add_element_by_index(TLinkedListItem *head, int index, char value);
int linked_list_count_elements(TLinkedListItem *head);
TLinkedListItem* linked_list_reverse (TLinkedListItem *head);
TLinkedListItem* linked_list_remove_all(TLinkedListItem *head);