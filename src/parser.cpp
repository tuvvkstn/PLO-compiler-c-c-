/*
 * parser.cpp
 *
 *  Created on: Sep 18, 2015
 *      Author: vuvantu
 */
#include <stdio.h>
#include <string.h>
#include "utils.h"

TokenType token;
int num;
char ident[MAX_IDENT_LEN + 1];
char ch;
int i;
FILE* reader;
void open(char* filename){
	reader = fopen(filename, "r");
	return ;
}
void close(char* filename){
	fclose(reader);
	return ;
}



char getChar(){
	char c = fgetc(reader);
//	printf("%c ", c);
	return c;
}
TokenType getToken(){
	if(ch == ' ' || ch == '\t' || ch == '\n'){
		while(ch == ' ' || ch == '\t' || ch == '\n')
			ch = getChar();
	}
	if(isLetter(ch)){
		i = 0;
		ident[i] = ch;
		while(1) {
			ch = getChar();
			if(isLetter(ch) || isDigit(ch)){
				i += 1;
				ident[i] = ch;
			}
			else{
				break;
			}
		}
		ident[i+1] = '\0';
		if(i > MAX_IDENT_LEN){
			printf("Ident %s qua dai, khong hop le\n", ident);
			return NONE;
		}
		if(isKeyword(ident)){
			return getTokenType(ident);
		}
		else{
			return IDENT;
		}
	}
	if(isDigit(ch)){
		i = 0;
		ident[i] = ch;
		while(1){
			ch = getChar();
			if(isDigit(ch)){
				i += 1;
				ident[i] = ch;
			}
			else{
				break;
			}
		}
		ident[i+1] = '\0';
		num = string2int(ident);
		return NUMBER;
	}
	if(ch == '+'){
		ch = getchar();
		ident[0] = '+';
		ident[1] = '\0';
		return PLUS;
	}
	if(ch == '*'){
		ch = getChar();
		ident[0] = '*';
		ident[1] = '\0';
		return TIMES;
	}
	if(ch == '-'){
		ch = getChar();
		ident[0] = '-';
		ident[1] = '\0';
		return MINUS;
	}
	if(ch == '/'){
		ch = getChar();
		return SLASH;
	}
	if(ch == '%'){
		ch = getChar();
		ident[0] = '%';
		ident[1] = '\0';
		return PERCENT;
	}
	if(ch == '='){
		ch = getChar();
		ident[0] = '=';
		ident[1] = '\0';
		return EQU;
	}
	if(ch == '<'){
		ch = getChar();
		if(ch == '>'){
			ch = getChar();
			ident[0] = '<';
			ident[1] = '>';
			ident[2] = '\0';
			return NEQ;
		}
		else if (ch == '='){
			ch = getChar();
			ident[0] = '<';
			ident[1] = '=';
			ident[2] = '\0';
			return LEQ;
		}
		else
			ident[0] = '<';
			ident[1] = '\0';
			return LSS;
	}
	if(ch == '>'){
		ch = getChar();
		if(ch == '='){
			ch = getChar();
			ident[0] = '>';
			ident[1] = '=';
			ident[2] = '\0';
			return GEQ;
		}
		else
			ident[0] = '>';
			ident[1] = '\0';
			return GTR;
	}
	if(ch == '('){
		ch = getChar();
		ident[0] = '(';
		ident[1] = '\0';
		return LPARENT;
	}
	if(ch == ')'){
		ch = getChar();
		ident[0] = ')';
		ident[1] = '\0';
		return RPARENT;
	}
	if(ch == '['){
		ident[0] = '[';
		ident[1] = '\0';
		ch = getChar();
		return LBRACK;
	}
	if(ch == ']'){
		ch = getChar();
		ident[0] = ']';
		ident[1] = '\0';
		return RBRACK;
	}
	if(ch == '.'){
		ch = getChar();
		ident[0] = '.';
		ident[1] = '\0';
		return PERIOD;
	}
	if(ch == ','){
		ch = getChar();
		ident[0] = ',';
		ident[1] = '\0';
		return COMMA;
	}
	if(ch == ';'){
		ch = getChar();
		ident[0] = ';';
		ident[1] = '\0';
		return SEMICOLON;
	}
	if(ch == ':'){
		ch = getChar();
		if(ch == '='){
			ch = getChar();
			ident[0] = ':';
			ident[1] = '=';
			ident[2] = '\0';
			return ASSIGN;
		}
		return NONE;
	}
	return NONE;
}

int main(){
	char filename[30];
	printf("Enter filename: ");
	scanf("%s", filename);
	open(filename);
	ch = ' ';
	do{
		token = getToken();
		if(token != NONE)
			printf("%s : %s\n",ident, tokenTypeChar[token]);
	}
	while(token != NONE);

	close(filename);
//	printf("End program!");
	return 0;
}
