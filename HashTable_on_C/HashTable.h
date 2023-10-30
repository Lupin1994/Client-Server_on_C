typedef struct HashTableItem THashTableItem;
struct HashTableItem
{
    char *key;
    char *value;
    //int count;
};

typedef struct HashTable THashTable;
struct HashTable
{
    THashTableItem **items;
    //int size;
    int count;
};

void hashTable_print(THashTable *hashTable);
void hashTable_printSearchValue(THashTable *hashTable, char *key);

THashTableItem* hashTable_createItem(char *key, char *value);
THashTable* hashTable_create();

unsigned long hashFunction(char *key);
void hashTable_collisionsProcessing(THashTable *hashtable, unsigned long key_index, THashTableItem *item);

void item_free(THashTableItem *item);
void hashTable_free(THashTable *hashTable);
void hashTable_addItem(THashTable *hashTable, char *key, char *value);
void hashTable_printSearchValue(THashTable *hashTable, char *key);
void hashTable_removeElement_byKey(THashTable *hashTable, char *key);