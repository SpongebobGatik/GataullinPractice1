#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
	char** elements; 
	int size; 
} Queue;

Queue* initQueue();

void QPUSH(Queue* queue, char* element);

char* QPOP(Queue* queue);

void saveToFileQueue(Queue* queue, const char* filename, const char* basename, int *pos1, int *pos2, int *status);

Queue* loadFromFileQueue(const char* filename, const char* basename, int *pos1, int *pos2, int *status);

#endif
