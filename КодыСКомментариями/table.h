#ifndef TABLE_H
#define TABLE_H

typedef struct NodeHashTable {
    char* element;
    int hash;
    struct NodeHashTable* next;
    struct NodeHashTable* prev;
} NodeHashTable;

typedef struct HashTable {
    NodeHashTable* head;
    int size;
    NodeHashTable** hashTable;
    int tableSize;
    char** keys;
} HashTable;

HashTable* initHashTable();

void HSET(HashTable* hashtable, char* key, char* value);

void HDEL(HashTable* hashtable, char* key);

char* HGET(HashTable* hashtable, char* key);

void saveToFileTable(HashTable* hashtable, const char* filename, const char* basename, int* pos1, int* pos2, int* status);

HashTable* loadFromFileTable(const char* filename, const char* basename, int* pos1, int* pos2, int* status);

#endif