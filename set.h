#ifndef SET_H
#define SET_H

typedef struct {
	char** elements;
	int size; 
} Set;

Set* initSet();

void SADD(Set* set, char* element);

void SREM(Set* set, char* element);

int SISMEMBER(Set* set, char* element);

void saveToFileSet(Set* set, const char* filename, const char* basename, int *pos1, int *pos2, int *status);

Set* loadFromFileSet(const char* filename, const char* basename, int *pos1, int *pos2, int *status);

#endif
