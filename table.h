#ifndef TABLE_H
#define TABLE_H

typedef struct {
    char** keys;
    char** values;
    int size;
} HashTable;

HashTable* initHashTable();

unsigned int hash(const char* key);

void HSET(HashTable* hashtable, char* key, char* value);

void HDEL(HashTable* hashtable, char* key);

char* HGET(HashTable* hashtable, char* key);

void saveToFileTable(HashTable* hashtable, const char* filename, const char* basename, int *pos1, int *pos2, int *status);

HashTable* loadFromFileTable(const char* filename, const char* basename, int *pos1, int *pos2, int *status);

#endif
