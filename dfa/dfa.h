﻿#pragma once

enum CharTypes {
	UNKNOWN,	
	VOL,	// [a-zA-Z]
	COLON,	
	BACK_SLASH,
	CHAR,	// [^*|\\:"<>?/]
	SPACE
};

int getCharType(char ch, int checkStrOrSubstr);
int checkString(const char* str);
void searchForSubstings(const char* str);