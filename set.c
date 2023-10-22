#define _CRT_SECURE_NO_WARNINGS
#include "set.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_SIZE 1000 

Set* initSet() {
	Set* set = (Set*)malloc(sizeof(Set));
	set->elements = (char**)malloc(MAX_SIZE * sizeof(char*));
	set->size = 0;
	return set;
}

void SADD(Set* set, char* element) {
	if (set->size >= MAX_SIZE) {
		printf("ћножество полно\n");
		return;
	}
	for (int i = 0; i < set->size; i++) {
		if (strcmp(set->elements[i], element) == 0) {
			printf("Ёлемент уже существует в множестве\n");
			return;
		}
	}
	set->elements[set->size] = _strdup(element);
	set->size++;
}

void SREM(Set* set, char* element) {
	for (int i = 0; i < set->size; i++) {
		if (strcmp(set->elements[i], element) == 0) {
			free(set->elements[i]);
			set->elements[i] = set->elements[set->size - 1];
			set->size--;
			return;
		}
	}
	printf("Ёлемент не найден в множестве\n");
}

int SISMEMBER(Set* set, char* element) {
	for (int i = 0; i < set->size; i++) {
		if (strcmp(set->elements[i], element) == 0) {
			return 1;
		}
	}
	return 0;
}

void saveToFileSet(Set* set, const char* filename, const char* basename, int *pos1, int *pos2, int *status) {
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
		if (ftell(tempFile) == *pos1 - 2  && *status == 2) fprintf(tempFile, "\t%s", set->elements[0]);
		else if (ftell(tempFile) == *pos1) {
			for (int i = 0; i < set->size; i++) {
				if (i == set->size - 1) fprintf(tempFile, "%s\n", set->elements[i]);
				else fprintf(tempFile, "%s\t", set->elements[i]);
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
	remove("2.data");
	rename("temp.data", "2.data");
}

Set* loadFromFileSet(const char* filename, const char* basename, int *pos1, int *pos2, int *status) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("ќшибка при открытии файла\n");
		return NULL;
	}
	Set* set = initSet();
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
	while (temp1 < temp2 + 1) {
		SADD(set, line[temp1]);
		temp1++;
	}
	fclose(file);
	return set;
}