#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <stdbool.h>
#include "HashTable.h"

#define HASHTABLE_SIZE 1000 // size our hash table 

void hashTable_print(THashTable *hashTable){
    printf("\n ------Hash Table------\n");
    printf("%d\n",hashTable->count);
    //printf("%s\n",hashTable->items[0]->value);
    for (int i = 0; i < hashTable->count; i++)
    {
        printf("{Key:%s : Value:%s}\n", hashTable->items[i]->key, hashTable->items[i]->value);
    }
    
    printf("\n -------THE END--------\n");
}


THashTableItem* hashTable_createItem(char *key, char *value){

    THashTableItem *item = (THashTableItem*)malloc(sizeof(THashTableItem));
    item->key = malloc(30 * sizeof(char));
    item->value = malloc(30 * sizeof(char));

    item->key = key;
    item->value = value;
    
    return item; 
}

THashTable* hashTable_create(){

    THashTable *hashTable = (THashTable*)malloc(sizeof(THashTable));
    //hashTable->size = 1000;
    hashTable->count = 0;
    hashTable->items = (THashTableItem**)calloc(HASHTABLE_SIZE, sizeof(THashTableItem*));

    for (int i = 0; i < HASHTABLE_SIZE; i++)
        hashTable->items[i] = NULL;

    return hashTable;
}

unsigned long hashFunction(char *key){
    unsigned long key_int = 0;
    size_t key_length = strlen(key);
    for (int i = 0; i < key_length ; i++)
    {
        key_int += key[i];
    }
    return key_int % HASHTABLE_SIZE; 
}

void item_free(THashTableItem *item){
    free (item->key);
    free (item);
}

void hashTable_free(THashTable *hashTable){
    for (int i=0; i < HASHTABLE_SIZE; i++) {
        THashTableItem *item = hashTable->items[i];
        if (item != NULL)
            item_free(item);
    }
    free (hashTable->items);
    free (hashTable);
}

void hashTable_collisionsProcessing(THashTable *hashtable, unsigned long key_index, THashTableItem *item){
    // линейные перебор элементов не очень эффективен, но остальные способы подразумевают
    // переход по элементам памяти с некоторым шагом, что уменьшает колличество итераций,
    // но влечет за собой другие проблемы при большой заполненности таблицы
    for (int i = key_index + 1; i < HASHTABLE_SIZE; i++)
    {
        if (hashtable->items[i] == NULL)
        {
            hashtable->items[i] = item; 
            hashtable->count++;
            return;
        }        
    }
}


void hashTable_addItem(THashTable *hashTable, char *key, char *value){
    if (hashTable->count == HASHTABLE_SIZE)
    {
        printf("Hash table is full\n");
        return; 
    }

    THashTableItem *item = hashTable_createItem(key , value);

    unsigned long key_index = hashFunction(key);

    THashTableItem *current_item = hashTable->items[key_index];

    if (current_item == NULL)
    {
        hashTable->items[key_index] = item;
        hashTable->count++;
        return;
    }

    hashTable_collisionsProcessing(hashTable, key_index, item);
}

char* hashTable_searchValue(THashTable *hashTable, char *key){
    int index = hashFunction(key);
    THashTableItem *item = hashTable->items[index];

    if (item != NULL)
    {
        return item->value;
    }

    return NULL;
}

void hashTable_printSearchValue(THashTable *hashTable, char *key){
    char *value = hashTable_searchValue(hashTable,key);
    if (value == NULL)
    {
        printf("Key:%s not found\n", key);
        return;
    }

    printf("{Key:%s, Value:%d\n}", key, *value);
}

void hashTable_removeElement_byKey(THashTable *hashTable, char *key){
    int index = hashFunction(key);
    if (hashTable->items[index] == NULL)
    {
        printf("\n Данного ключа не существует \n");
        return;
    }

    item_free(hashTable->items[index]);
    hashTable->count--;
    printf("\n Ключ (%s) удален \n", key);

}