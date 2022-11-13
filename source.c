#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 64
#define MAX_LENGTH 1024

#pragma region Struct
typedef struct Node* Position;
struct Node {
	int _data;
	Position _link;
} *top = NULL;
#pragma endregion

#pragma region Declaration
char* Read_From_File(char*);
int Push(int);
int Pop(void);
int isAlone(void);
int Compile(char*);
#pragma endregion


int main(void)
{
	int result = 0;
	char* buffer = "";
	char* file_name[MAX];
	printf("What file do you want to access: ");
	scanf(" %s", file_name);

	buffer = Read_From_File(file_name);
	result = Compile(buffer);
	printf("Result is: %d", result);
	free(top);
	return EXIT_SUCCESS;
}

#pragma region Functions
char* Read_From_File(char* file_name)
{
	char* buffer = malloc(MAX_LENGTH);

	FILE* fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Access denied");
		exit(1);
	}

	fgets(buffer, MAX, fp);
	return buffer;
}
int Compile(char* buffer) {

	int a = 0;
	int b = 0;
	int count = 0;
	char value;
	while (strlen(buffer) > 0)
	{
		sscanf(buffer, "%c %n", &value, &count);

		if (value >= '0' && value <= '9')
			Push(value - '0');
		else {
			a = Pop();
			b = Pop();
			switch (value) {
			case '+':
				Push(b + a); break;
			case '-':
				Push(b - a); break;
			case '/':
				Push(b / a); break;
			case '*':
				Push(b * a); break;
			}
		}
		buffer += count;
	}
	if (isAlone())
		return Pop();
	printf("Program se nije uspješno izvršio!");
	exit(1);
}
int Push(int data)
{
	Position new_node = (Position)malloc(sizeof(struct Node));
	if (new_node == NULL)
	{
		printf("Stack Overflow");
		exit(1);
	}
	new_node->_data = data;
	new_node->_link = NULL;

	new_node->_link = top;
	top = new_node;

	return EXIT_SUCCESS;
}

int Pop()
{
	Position temp;
	temp = top;
	int value = temp->_data;

	top = top->_link;
	free(temp);
	temp = NULL;

	return value;
}

int isAlone()
{
	if (top != NULL && top->_link == NULL)
		return 1;
	return 0;
}
#pragma endregion

