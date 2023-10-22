#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <locale.h>
#include "stack.h"
#include "set.h"
#include "queue.h"
#include "table.h"
#define MAX_SIZE 1000 // максимальный размер стека 

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Russian");
	char* filename = NULL;
	char* query = NULL;
	char* item = NULL;
	char* basename = NULL;
	char* key = NULL;
	int temp;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
			filename = argv[i + 1];
		}
		else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
			query = argv[i + 1];
			temp = i + 1;
			basename = argv[i + 2];
			if (i + 5 > argc) item = argv[i + 3];
			else {
				key = argv[i + 3];
				item = argv[i + 4];
			}
		}
	}
	if (filename != NULL && query != NULL) {
		FILE* file = fopen(filename, "r");
		if (!file) FILE* file = fopen(filename, "w");
		int pos1 = 0;;
		int pos2 = 0;;
		int status = 0;;
		if (strcmp(argv[temp], "SPUSH") == 0) {
			Stack* stack = loadFromFileStack(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				SPUSH(stack, item);
				printf("-> %s\n", item);
				if (status == 1) status = 0;
				fclose(file);
				saveToFileStack(stack, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "SPOP") == 0) {
			Stack* stack = loadFromFileStack(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				char* element = SPOP(stack);
				printf("-> %s\n", element);
				if (status == 2) status = 0;
				fclose(file);
				saveToFileStack(stack, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "SADD") == 0) {
			Set* set = loadFromFileSet(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				SADD(set, item);
				printf("-> %s\n", item);
				if (status == 1) status = 0;
				fclose(file);
				saveToFileSet(set, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "SREM") == 0) {
			Set* set = loadFromFileSet(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				SREM(set, item);
				printf("-> %s\n", item);
				if (status == 2) status = 0;
				fclose(file);
				saveToFileSet(set, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "SISMEMBER") == 0) {
			Set* set = loadFromFileSet(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				if (SISMEMBER(set, item)) printf("-> True\n");
				else printf("-> False\n");
				fclose(file);
			}
		}
		if (strcmp(argv[temp], "QPUSH") == 0) {
			Queue* queue = loadFromFileQueue(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				QPUSH(queue, item);
				printf("-> %s\n", item);
				if (status == 1) status = 0;
				fclose(file);
				saveToFileQueue(queue, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "QPOP") == 0) {
			Queue* queue = loadFromFileQueue(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				char* element = QPOP(queue);
				printf("-> %s\n", element);
				if (status == 2) status = 0;
				fclose(file);
				saveToFileQueue(queue, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "HSET") == 0) {
			HashTable* hashtable = loadFromFileTable(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				HSET(hashtable, item, key);
				printf("-> %s %s\n", item, key);
				if (status == 1) status = 0;
				fclose(file);
				saveToFileTable(hashtable, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "HDEL") == 0) {
			HashTable* hashtable = loadFromFileTable(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				HDEL(hashtable, item);
				printf("-> %s\n", item);
				if (status == 2) status = 0;
				fclose(file);
				saveToFileTable(hashtable, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "HGET") == 0) {
			HashTable* hashtable = loadFromFileTable(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				if (HGET(hashtable, item) != NULL) printf("-> True\n");
				else printf("-> False\n");
				fclose(file);
			}
		}
	}
	else {
		printf("Не указано имя файла или выполняемая операция.\n");
		system("pause");
		return 1;
	}
	system("pause");
	return 0;
}
