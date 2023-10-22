#define _CRT_SECURE_NO_WARNINGS
#include "stack.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_SIZE 1000 

Stack* initStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->elements = (char**)malloc(MAX_SIZE * sizeof(char*));
	stack->top = -1;
	return stack;
}

void SPUSH(Stack* stack, char* element) {
	if (stack->top >= MAX_SIZE - 1) {
		printf("Стек полон\n");
		return;
	}
	stack->top++;
	stack->elements[stack->top] = _strdup(element);
}

char* SPOP(Stack* stack) {
	if (stack->top < 0) {
		printf("Стек пуст\n");
		return NULL;
	}
	char* element = stack->elements[stack->top];
	stack->top--;
	return element;
}

void saveToFileStack(Stack* stack, const char* filename, const char* basename, int *pos1, int *pos2, int *status) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Ошибка при открытии файла\n");
		return;
	}
	FILE* tempFile = fopen("temp.data", "w");
	if (tempFile == NULL) {
		printf("Ошибка при открытии временного файла\n");
		fclose(file);
		return;
	}

	int ch;
	fseek(file, 0, SEEK_SET);
	fseek(tempFile, 0, SEEK_SET);
	while ((ch = fgetc(file)) != EOF) {
		fputc(ch, tempFile);
		if (ftell(tempFile) == *pos1 - 2 && *status == 2) fprintf(tempFile, "\t%s", stack->elements[0]);
		else if (ftell(tempFile) == *pos1) {
			for (int i = 0; i <= stack->top; i++) {
				if (i == stack->top) fprintf(tempFile, "%s\n", stack->elements[i]);
				else fprintf(tempFile, "%s\t", stack->elements[i]);
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

Stack* loadFromFileStack(const char* filename, const char* basename, int *pos1, int *pos2, int *status) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Ошибка при открытии файла\n");
		return NULL;
	}
	Stack* stack = initStack();
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
	if (count > 1) printf("\nТаких баз данных несколько, операции выполняются с последней!\n");
	if (temp1 == temp2) *status = 1;
	if (temp1 == temp2 + 1) *status = 2;
	while (temp1 < temp2 + 1) {
		SPUSH(stack, line[temp1]);
		temp1++;
	}
	fclose(file);
	return stack;
}