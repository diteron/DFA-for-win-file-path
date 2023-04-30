#pragma once

// Regex: ([a-zA-Z]:\\)([^*|\\:"<>?/]+)(\\([^*|\\:"<>?/]+))
// 
// [a-zA-Z]				vol
// [^ *| \\:"<>?/]+		char
// 
// vol:\\ char+ (\\char+)*		validString


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