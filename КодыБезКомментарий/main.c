#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <locale.h>
#include "stack.h"
#include "set.h"
#include "queue.h"
#include "table.h"

void removeNewline(char* str);

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Russian");
	char* filename = NULL;
	char* query = NULL;
	char* item = NULL;
	char* basename = NULL;
	char* key = NULL;
	int temp;
	if (argc < 5 || argc > 8) {
		printf("Неверное количество аргументов.\n");
		return 1;
	}
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
			filename = argv[i + 1];
		}
		else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
			query = argv[i + 1];
			temp = i + 1;
			basename = argv[i + 2];
			if (i + 5 > argc) key = argv[i + 3];
			else {
				key = argv[i + 3];
				item = argv[i + 4];
				if (key == NULL || item == NULL) {
					printf("Ключ или Объект не введены.\n");
					return 1;
				}
				removeNewline(key);
				removeNewline(item);
			}
			if (key != NULL) removeNewline(key);
		}
	}
	if (filename != NULL && query != NULL) {
		FILE* file = fopen(filename, "r");
		if (!file) {
			printf("Такого файла нет!\n");
		}
		removeNewline(basename);
		int pos1 = 0;
		int pos2 = 0;
		int status = 0;
		if (strcmp(argv[temp], "SPUSH") == 0) {
			if (key == NULL) {
				printf("Объект не введён.\n");
				return 1;
			}
			Stack* stack = loadFromFileStack(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				SPUSH(stack, key);
				printf("-> %s\n", key);
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
			if (key == NULL) {
				printf("Объект не введён.\n");
				return 1;
			}
			Set* set = loadFromFileSet(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				SADD(set, key);
				printf("-> %s\n", key);
				if (status == 1) status = 0;
				fclose(file);
				saveToFileSet(set, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "SREM") == 0) {
			if (key == NULL) {
				printf("Объект не введён.\n");
				return 1;
			}
			Set* set = loadFromFileSet(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				SREM(set, key);
				printf("-> %s\n", key);
				if (status == 2) status = 0;
				fclose(file);
				saveToFileSet(set, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "SISMEMBER") == 0) {
			if (key == NULL) {
				printf("Объект не введён.\n");
				return 1;
			}
			Set* set = loadFromFileSet(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				if (SISMEMBER(set, key)) printf("-> True\n");
				else printf("-> False\n");
				fclose(file);
			}
		}
		if (strcmp(argv[temp], "QPUSH") == 0) {
			if (key == NULL) {
				printf("Объект не введён.\n");
				return 1;
			}
			Queue* queue = loadFromFileQueue(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				QPUSH(queue, key);
				printf("-> %s\n", key);
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
			if (key == NULL || item == NULL) {
				printf("Ключ или Объект не введены.\n");
				return 1;
			}
			HashTable* hashtable = loadFromFileTable(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				HSET(hashtable, key, item);
				printf("-> %s %s\n", item, key);
				if (status == 1) status = 0;
				fclose(file);
				saveToFileTable(hashtable, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "HDEL") == 0) {
			if (key == NULL) {
				printf("Объект не введён.\n");
				return 1;
			}
			HashTable* hashtable = loadFromFileTable(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				HDEL(hashtable, key);
				printf("-> %s\n", key);
				if (status == 2) status = 0;
				fclose(file);
				saveToFileTable(hashtable, filename, basename, &pos1, &pos2, &status);
			}
		}
		if (strcmp(argv[temp], "HGET") == 0) {
			if (key == NULL) {
				printf("Объект не введён.\n");
				return 1;
			}
			HashTable* hashtable = loadFromFileTable(filename, basename, &pos1, &pos2, &status);
			if (pos1 + pos2 == 0) {
				printf("Такой базы данных, увы, нет!\n");
				fclose(file);
			}
			else {
				if (HGET(hashtable, key) != NULL) printf("-> True\n");
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

void removeNewline(char* str) {
	if (str != NULL) {
		size_t length = strcspn(str, "\n");
		str[length] = '\0';
	}
}