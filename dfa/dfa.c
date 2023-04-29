#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dfa.h"

#define TRUE 1
#define FALSE 0

#define CHECK_STR 1	
#define CHECK_SUBSTR 0

#define STATES_NUM 6
#define CHARS_NUM 5
#define MAX_PATH_LENGTH 257

const int states[STATES_NUM] =		 { 0,     1,     2,     3,     4,     5 };
const int isFinalState[STATES_NUM] = { FALSE, FALSE, FALSE, FALSE, FALSE, TRUE };

const int transitions[STATES_NUM][CHARS_NUM] = {
	{0, 0, 0, 0, 0},	// unknown
	{0, 2, 0, 0, 0},
	{0, 0, 3, 0, 0},
	{0, 0, 0, 4, 0},
	{0, 0, 0, 0, 5},
	{0, 0, 0, 4, 5},
};

const char invalidChars[] = { '*', '|','\"', '<', '>', '?', '/' };
const int invalidCharsNum = sizeof(invalidChars) / sizeof(char);

int main(void) {
	printf("1. Check string\n"
		   "2. Search for correct substrings in a string\n\n");

	int choice;
	scanf_s("%d%*c", &choice);

	char str[MAX_PATH_LENGTH] = "";
	switch (choice) {
	case 1:
		printf("Enter string to check:\n");
		fgets(str, MAX_PATH_LENGTH, stdin);
		if (checkString(str)) {
			printf("Correct path\n");
		}
		else {
			printf("Incorrect path\n");
		}
		break;

	case 2:
		printf("Enter string for substrings search:\n");
		fgets(str, MAX_PATH_LENGTH, stdin);
		searchForSubstings(str);
		break;

	default:
		printf("Incorrect choice\n");
		system("pause");
		return 1;
	}
	
	system("pause");
	return 0;
}

int getCharType(char ch, int checkStrOrSubstr) {
	static int volReaded = FALSE;
	int isVol = (ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90);

	// Если осуществляется поиск подстрок, то пробел используется как разделитель. При его появлении в строке он возвращает
	// переменную volReaded в изначальное состояние, для чтения нового пути
	if (ch == ' ' && volReaded && checkStrOrSubstr == CHECK_SUBSTR) {
		volReaded = FALSE;
		return SPACE;
	}
	else if (!volReaded && isVol) {	// [a-zA-Z]
		volReaded = TRUE;
		return VOL;
	}
	else if (ch == ':') {
		return COLON;
	}
	else if (ch == '\\') {
		return BACK_SLASH;
	}
	else {		
		for (int i = 0; i < invalidCharsNum; ++i) {	// Символ строки не должен быть равным *, |, ", <, >, ?, или /
			if (ch == invalidChars[i]) {
				return UNKNOWN;
			}
		}
		return CHAR;
	}
}

int checkString(const char* str) {
	size_t strLength = strlen(str);
	int state = 1;

	for (int i = 0; i < strLength; ++i) {
		state = transitions[state][getCharType(str[i], CHECK_STR)];
	}

	return isFinalState[state];
}

void searchForSubstings(const char* str) {
	size_t strLength = strlen(str);

	printf("Correct substrings in the string:\n");

	int state = 1;
	int charType;
	char subStr[MAX_PATH_LENGTH] = "";
	for (int i = 0, j = 0; i <= strLength; ++i, ++j) {
		charType = getCharType(str[i], CHECK_SUBSTR);
		
		if (charType == SPACE || str[i] == '\0') {
			if (isFinalState[state]) {		// Выводим строку только тогда, когда автомат находится в принимающем состоянии
				subStr[j] = '\0';
				printf("%s\n", subStr);
			}

			j = -1;		// Возвращаем индекс заполняемой подстроки в начало
			state = 1;
			continue;
		}
		
		state = transitions[state][charType];
		subStr[j] = str[i];
	}
}