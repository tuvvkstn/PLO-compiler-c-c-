/*
 * parser.cpp
 *
 *  Created on: Sep 18, 2015
 *      Author: vuvantu
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


TokenType token;
int line_num = 1;
int num;
char ident[MAX_IDENT_LEN + 1];
char ch;
char filename[30]=  "inputFile/prog1.PL0";
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
		if(ch == '\n') line_num += 1;
		while(ch == ' ' || ch == '\t' || ch == '\n'){
			ch = getChar();
			if(ch == '\n') line_num += 1;
		}
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
			printf("%s - %s\n", ident, tokenTypeChar[getTokenType(ident)]);
			return getTokenType(ident);
		}
		else{
			printf("%s - %s\n", ident, tokenTypeChar[IDENT]);
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
		printf("%s - %s\n", ident, tokenTypeChar[NUMBER]);
		return NUMBER;
	}
	if(ch == '+'){
		ch = getchar();
		ident[0] = '+';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[PLUS]);
	return PLUS;
	}
	if(ch == '*'){
		ch = getChar();
		ident[0] = '*';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[TIMES]);
		return TIMES;
	}
	if(ch == '-'){
		ch = getChar();
		ident[0] = '-';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[MINUS]);
		return MINUS;
	}
	if(ch == '/'){
		ch = getChar();
		printf("%s - %s\n", ident, tokenTypeChar[SLASH]);
		return SLASH;
	}
	if(ch == '%'){
		ch = getChar();
		ident[0] = '%';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[PERCENT]);
		return PERCENT;
	}
	if(ch == '='){
		ch = getChar();
		ident[0] = '=';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[EQU]);
		return EQU;
	}
	if(ch == '<'){
		ch = getChar();
		if(ch == '>'){
			ch = getChar();
			ident[0] = '<';
			ident[1] = '>';
			ident[2] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[NEQ]);
			return NEQ;
		}
		else if (ch == '='){
			ch = getChar();
			ident[0] = '<';
			ident[1] = '=';
			ident[2] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[LEQ]);
			return LEQ;
		}
		else
			ident[0] = '<';
			ident[1] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[LSS]);
			return LSS;
	}
	if(ch == '>'){
		ch = getChar();
		if(ch == '='){
			ch = getChar();
			ident[0] = '>';
			ident[1] = '=';
			ident[2] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[GEQ]);
			return GEQ;
		}
		else
			ident[0] = '>';
			ident[1] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[GTR]);
			return GTR;
	}
	if(ch == '('){
		ch = getChar();
		ident[0] = '(';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[LPARENT]);
		return LPARENT;
	}
	if(ch == ')'){
		ch = getChar();
		ident[0] = ')';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[RPARENT]);
		return RPARENT;
	}
	if(ch == '['){
		ident[0] = '[';
		ident[1] = '\0';
		ch = getChar();
		printf("%s - %s\n", ident, tokenTypeChar[LBRACK]);
		return LBRACK;
	}
	if(ch == ']'){
		ch = getChar();
		ident[0] = ']';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[RBRACK]);
		return RBRACK;
	}
	if(ch == '.'){
		ch = getChar();
		ident[0] = '.';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[PERIOD]);
		return PERIOD;
	}
	if(ch == ','){
		ch = getChar();
		ident[0] = ',';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[COMMA]);
		return COMMA;
	}
	if(ch == ';'){
		ch = getChar();
		ident[0] = ';';
		ident[1] = '\0';
		printf("%s - %s\n", ident, tokenTypeChar[SEMICOLON]);
		return SEMICOLON;
	}
	if(ch == ':'){
		ch = getChar();
		if(ch == '='){
			ch = getChar();
			ident[0] = ':';
			ident[1] = '=';
			ident[2] = '\0';
			printf("%s - %s\n", ident, tokenTypeChar[ASSIGN]);
			return ASSIGN;
		}
		printf("%s - %s\n", ident, tokenTypeChar[NONE]);
		return NONE;
	}
	printf("%s - %s\n", ident, tokenTypeChar[NONE]);
	return NONE;
}

int main(int argc, char *argv[]){
//	printf("Enter filename: ");
//	scanf("%s", filename);
	open(filename);
	ch = ' ';
	token = getToken();
	program();
//	close(filename);
//	printf("program ok!");
	return 0;
}
void program(){
	if(token == PROGRAM){
		token = getToken();
		if(token == IDENT){
			token = getToken();
			if(token == SEMICOLON){
				token = getToken();
				block();
				if(token == PERIOD){
					printf("Thanh cong!\n");
				}
				else{
					error_display("[In program] Thieu dau cham.\n");
				}
			}
			else{
				error_display("[In program] Thieu dau cham phay.\n");
			}
		}
		else {
			error_display("[In program] Thieu ten chuong trinh.\n");
		}
	}
	else {
		error_display("Thieu tu khoa PROGRAM.\n");
	}
	return ;
}
void block(){
	switch (token) {
	case CONST:
		do{
			token = getToken();
			if(token == IDENT){
				token = getToken();
				if(token ==EQU){
					token = getToken();
					if(token == NUMBER){
						token = getToken();
					}
					else{
						error_display("[in block -> CONST] Thieu so sau trong bieu thuc.\n");
					}
				}
				else{
					error_display("[in block -> CONST] Thieu dau bang sau dinh danh.\n");
				}
			}
			else {
				error_display("[in block > CONST] Thieu ten.\n");
			}
		} while(token == COMMA);

		if(token == SEMICOLON){
			token = getToken();
			block();
		}
		else{
			error_display("[in block] Thieu dau cham phay ket thuc khai bao CONST.\n");
		}
		break;
	case VAR:
		do {
			token = getToken();
			if(token == IDENT){
				token = getToken();
				if(token == LBRACK){
					token = getToken();
					if(token == NUMBER){
						token = getToken();
						if(token == RBRACK){
							token = getToken();
						}
						else{
							error_display("[in block -> VAR] Thieu dong ngoac vuong sau khai bao mang.\n");
						}
					}
					else{
						error_display("[in block -> VAR] Thieu so trong khai bao mang.\n");
					}
				}

			}
			else{
				error_display("[in block -> VAR] Thieu dinh danh.\n");
			}
		}
		while(token == COMMA);

		if(token == SEMICOLON){
			token = getToken();
			block();
		}
		else{
			error_display("[in block -> VAR] Thieu dau cham phay sau khai bao bien.\n");
		}
		break;
	case PROCEDURE:
		token = getToken();
		if(token == IDENT){
			token = getToken();
			if(token == LPARENT){
				do {
					token = getToken();
					if(token == VAR){
						token = getToken();
					}
					if(token == IDENT){
						token = getToken();
					}
					else{
						error_display("[in block -> PROCEDURE] Thieu ten bien trong khai bao thu tuc.\n");
					}
				} while(token == SEMICOLON);
				if(token == RPARENT){
					token = getToken();
				}
				else{
					error_display("[in block -> PROCEDURE] Thieu dau dong ngoac.\n");
				}
			}

			if(token == SEMICOLON){
				token = getToken();
				block();
				if(token == SEMICOLON){
					token = getToken();
					block();
				}
				else{
					error_display("[in block -> PROCEDURE] Thieu dau cham phay sau khoi block.\n");
				}
			}
			else{
				error_display("[in block -> PROCEDURE] Khoi PROCEDURE sai.\n");
			}
		}
		else{
			error_display("[in block -> PROCEDURE] Thieu ten thu tuc.\n");
		}
		break;
	case BEGIN:
		token = getToken();
		statement();
		while(token == SEMICOLON){
			token = getToken();
			statement();
		}
		if(token == END){
			token = getToken();
		}
		else{
			error_display("[in block -> BEGIN] Thieu END.\n");
		}
		break;
	default:
		error_display("[in block] Block begin error.\n");
	}//end switch case

	return ;
}
void statement(){
	switch (token) {
		case IDENT:
			token = getToken();
			if(token == RBRACK){
				token = getToken();
				expression();
				if(token == RBRACK){
					token = getToken();
				}
				else{
					error_display("[in statement -> IDENT] Thieu dau dong ngoac vuong.\n");
				}
			}
			if(token == ASSIGN){
				token = getToken();
				expression();
			}
			else {
				error_display("[in statement -> IDENT] Thieu dau gan.\n");
			}
			break;
		case CALL:
			token = getToken();
			if(token == IDENT){
				token = getToken();
				if(token == LPARENT){
					do {
						token = getToken();
						expression();
					} while(token == COMMA);
					if(token == RPARENT){
						token = getToken();
					}
					else{
						error_display("[in statement -> CALL] Thieu dau dong ngoac.\n");
					}
				}
			}
			else {
				error_display("[in statement -> CALL] Thieu ten thu tuc khi goi.\n");
			}
			break;
		case BEGIN:
			token = getToken();
			statement();
			while(token == SEMICOLON){
				token = getToken();
				statement();
			}
			if(token == END){
				token = getToken();
			}
			else{
				error_display("[in statement -> BEGIN] Thieu END.\n");
			}
			break;
		case IF:
			token = getToken();
			condition();
			if(token == THEN){
				token = getToken();
				statement();
			}
			else{
				error_display("[in statement -> IF] Thieu Then sau if.\n");
			}
			break;
		case WHILE:
			token = getToken();
			condition();
			if(token == DO){
				token = getToken();
				statement();
			}
			else{
				error_display("[in statement -> WHILE] Thieu DO sau WHILE.\n");
			}
			break;
		case FOR:
			token = getToken();
			if(token == IDENT){
				token = getToken();
				if(token == ASSIGN){
					token = getToken();
					expression();
					if(token == TO){
						token = getToken();
						expression();
						if(token == DO){
							token = getToken();
							statement();
						}
						else{
							error_display("[in statement -> FOR] Thieu DO.\n");
						}
					}
					else {
						error_display("[in statement -> FOR] Thieu TO.\n");
					}
				}
				else {
					error_display("[in statement -> FOR] Thieu phep gan.\n");
				}
			}
			else{
				error_display("[in statement -> FOR] Thieu ten bien.\n");
			}
			break;
		default:
			error_display("[in statement] Khoi statement sai.\n");
			break;
	}

	return ;
}
void condition(){
	if(token == ODD){
		token = getToken();
		expression();
	}
	expression();
	if(token == EQU || token == GTR || token == GEQ
			|| token == LSS || token == LEQ || token == NEQ){
		token = getToken();
		expression();
	}
	else {
		error_display("[in condition -> expression] Bieu thuc dieu kien khong hop le.\n");
	}
	return;
}
void expression(){
	if(token == PLUS || token == MINUS){
		token = getToken();
	}
	term();
	while(token == PLUS || token == MINUS){
		term();
	}
	return ;
}
void term(){
	factor();
	while(token == TIMES || token == PERCENT || token == SLASH){
		token = getToken();
		factor();
	}
	return;
}
void factor(){
	switch (token) {
		case IDENT:
			token = getToken();
			if(token == RBRACK){
				token = getToken();
				expression();
				if(token == LBRACK){
					token = getToken();
				}
				else {
					error_display("[in factor -> IDENT] Thieu dong ngoac vuong.\n");
				}
			}
			break;
		case NUMBER:
			token = getToken();
			break;
		case LPARENT:
			token = getToken();
			expression();
			if(token == RPARENT){
				token = getToken();
			}
			else {
				error_display("[in factor] Thieu dau dong ngoac.\n");
			}
			break;
		default:
			error_display("[in factor] Khoi factor sai.\n");
			break;
	}
	return;
}
void error_display(const char* err_msg){
	printf("Line number %d, %s",line_num, err_msg);
//	close(filename);
//	exit(-1);
	return;
}
