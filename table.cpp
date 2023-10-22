#define _CRT_SECURE_NO_WARNINGS
#include "table.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_SIZE 1000 

HashTable* initHashTable() {
	HashTable* hashtable = (HashTable*)malloc(sizeof(HashTable));
	hashtable->keys = (char**)malloc(MAX_SIZE * sizeof(char*));
	hashtable->values = (char**)malloc(MAX_SIZE * sizeof(char*));
	hashtable->size = 0;
	return hashtable;
}

unsigned int hash(const char* key) {
	unsigned int h = 0;
	for (int i = 0; key[i] != '\0'; i++) {
		h = 31 * h + key[i];
	}
	return h % MAX_SIZE;
}

void HSET(HashTable* hashtable, char* key, char* value) {
	
	if (hashtable->size >= MAX_SIZE) {
		printf("’еш-таблица полна\n");
		return;
	}

	for (int i = 0; i < hashtable->size; i++) {
		if (strcmp(hashtable->keys[i], key) == 0) {
			printf("Ёлемент уже существует в хеш-таблице\n");
			return;
		}
	}

	hashtable->keys[hashtable->size] = _strdup(key);
	hashtable->values[hashtable->size] = _strdup(value);
	hashtable->size++;
}

void HDEL(HashTable* hashtable, char* key) {
	for (int i = 0; i < hashtable->size; i++) {
		if (strcmp(hashtable->keys[i], key) == 0) {
			free(hashtable->keys[i]);
			free(hashtable->values[i]);
			hashtable->keys[i] = hashtable->keys[hashtable->size - 1];
			hashtable->values[i] = hashtable->values[hashtable->size - 1];
			hashtable->size--;
			return;
		}
	}
	printf("Ёлемент не найден в хеш-таблице\n");
}

char* HGET(HashTable* hashtable, char* key) {
	for (int i = 0; i < hashtable->size; i++) {
		if (strcmp(hashtable->keys[i], key) == 0) {
			return hashtable->values[i];
		}
	}
	return NULL;
}

void saveToFileTable(HashTable* hashtable, const char* filename, const char* basename, int *pos1, int *pos2, int *status) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("ќшибка при открытии файла\n");
		return;
	}
	FILE* tempFile = fopen("temp.data", "w");
	if (tempFile == NULL) {
		printf("ќшибка при открытии временного файла\n");
		fclose(file);
		return;
	}
	int ch;
	fseek(file, 0, SEEK_SET);
	fseek(tempFile, 0, SEEK_SET);
	while ((ch = fgetc(file)) != EOF) {
		fputc(ch, tempFile);
		if (ftell(tempFile) == *pos1 - 2 && *status == 2) fprintf(tempFile, "\t%s\t%s", hashtable->keys[0], hashtable->values[0]);
		else if (ftell(tempFile) == *pos1) {
			for (int i = 0; i <= hashtable->size - 1; i++) {
				if (i == hashtable->size - 1) fprintf(tempFile, "%s\t%s\n", hashtable->keys[i], hashtable->values[i]);
				else fprintf(tempFile, "%s\t%s\t", hashtable->keys[i], hashtable->values[i]);
			}
			if (*status == 1) {
				fseek(tempFile, *pos1 - 1, SEEK_SET);
				fprintf(tempFile, "\n");
			}
			fseek(file, *pos2, SEEK_SET);
		}
	}

	fclose(file);
	fclose(tempFile);
	remove(filename);
	rename("temp.data", filename);
}

HashTable* loadFromFileTable(const char* filename, const char* basename, int *pos1, int *pos2, int *status) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("ќшибка при открытии файла\n");
		return NULL;
	}
	HashTable* hashtable = initHashTable();
	char line[1000][1000];
	int tempory = 0;
	int tempory2 = 0;
	int count = 0;
	int temp1 = 0;
	int temp2 = 0;
	char c = '1';
	for (int i = 0; i < 1000; ++i) {
		fscanf(file, "%s", line[i]);
		c = getc(file);
		if (c == '\n') {
			tempory2 = ftell(file);
		}
		if (!strcmp(line[i], basename) && (tempory2 == ftell(file) || tempory2 == ftell(file) - strlen(line[i]) - 1 || i == 0)) {
			tempory = 1;
			*pos1 = ftell(file);
			*pos2 = strlen(line[i]);
			temp1 = i + 1;
		}
		if (c == '\n' && tempory == 1) {
			temp2 = i;
			*pos2 = ftell(file);
			tempory = 0;
			count++;
		}
		if (feof(file))
			break;
	}
	if (count > 1) printf("\n“аких баз данных несколько, операции выполн€ютс€ с последней!\n");
	if (temp1 == temp2) *status = 1;
	if (temp1 == temp2 + 1) *status = 2;
	while (temp1 < temp2) {
		char* key = line[temp1];
		char* value = line[temp1+1];
		HSET(hashtable, key, value);
		temp1 += 2;
		if (temp1 == temp2) printf("\nѕоследний элемент возможно был удалЄн, так как он без ключа!\n");
	}
	fclose(file);
	return hashtable;
}