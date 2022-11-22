#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "compiler.h"

#define MAX_IDENT_LENGTH 11
#define MAX_NUM_LENGTH 5
#define ERR_IDENT_LENGTH 1
#define ERR_NUM_LENGTH 2
#define ERR_INVALID_IDENT 3
#define ERR_INVALID_SYMBOL 4
#define ERR_INVALID_IDENT_NAME 5

int keyword_check(char buffer[]);
void print_lexeme_list(lexeme *list, int list_end);

lexeme *lex_analyze(int list_flag, char *input)
{
	int lex_index = 0, index = 0, buffer_index = 0;
	int error = 0;
	lexeme lexeme[ARRAY_SIZE];
	char buffer[MAX_IDENT_LENGTH + 1];

	while(input[index] != '\0') {
		if(isalnum(input[index])) {
			while(buffer_index < MAX_IDENT_LENGTH && isalnum(input[index])) {
				buffer[buffer_index] = input[index];
				index++;
				buffer_index++;
			}
			buffer[buffer_index] = '\0';
			if(isalnum(input[index])) {
				// If you stop adding chars to buffer and next char is letter or digit "ERR_IDENT_LENGTH"
				lexeme[lex_index].error_type = ERR_IDENT_LENGTH;
				lexeme[lex_index].type = -1;
				lex_index++;
				// Move past any remaining letters and digits before going to next token
			}
			else if(keyword_check(buffer) != -1) {
				// copy buffer to identifier_name field to set token type
				strcpy(lexeme[lex_index].identifier_name, buffer);
			 }
			else {
				// "ERR_INVALID_IDENT_NAME"
				lexeme[lex_index].error_type = ERR_INVALID_IDENT_NAME;
				lexeme[lex_index].type = -1;
				lex_index++;
			}
		}
		if(isdigit(input[index])) {
			// Add chars to buffer while they are digits and you have space in buffer up to (MAX_NUM_LENGTH)
			// reset buffer index in case used above
			buffer_index = 0;
			while(isdisigit(input[index]) && buffer_index < MAX_NUM_LENGTH) {
				buffer[buffer_index] = input[index];
				buffer_index++;
				index++;
			}
			buffer[buffer_index] = '\0';
			if(isdigit(input[index])) {
				lexeme[lex_index].error_type = ERR_NUM_LENGTH;
				lexeme[lex_index].type = -1;
				lex_index++;
				// Move past any remaining digits or letters before moving to next token
			}
			else if(isalpha(input[index])){
				lexeme[lex_index].error_type = ERR_INVALID_IDENT;
				lexeme[lex_index].type = -1;
				lex_index++;
				// Move past any remaining digits or letters before moving to next token
			}
			else {
				lexeme[lex_index].number_value = atoi(buffer);
				// number value = buffer
			}

		}
		if(input[index] == '?') {
			// Begin with '?' move past all chars until you reach a '\n' or '\0'
		}
		if(isspace(input[index])) {
			// Skip
		}	
		else {
			// proccess with if-else-if or switch structure (Don't use string.h for symbols)
				// Single char symbols
				//'.', '-', ';', '{', '}', '+', '*', '/', '(', ')'
				// Double char symbols
				// ":=", "==", "<", "<=", ">", ">=", "!="
				// Else  "ERR_INVALID_SYMBOL"
		}			
	}
}

int keyword_check(char buffer[])
{
	if (strcmp(buffer, "const") == 0)
		return keyword_const;
	else if (strcmp(buffer, "var") == 0)
		return keyword_var;
	else if (strcmp(buffer, "procedure") == 0)
		return keyword_procedure;
	else if (strcmp(buffer, "call") == 0)
		return keyword_call;
	else if (strcmp(buffer, "begin") == 0)
		return keyword_begin;
	else if (strcmp(buffer, "end") == 0)
		return keyword_end;
	else if (strcmp(buffer, "if") == 0)
		return keyword_if;
	else if (strcmp(buffer, "then") == 0)
		return keyword_then;
	else if (strcmp(buffer, "while") == 0)
		return keyword_while;
	else if (strcmp(buffer, "do") == 0)
		return keyword_do;
	else if (strcmp(buffer, "read") == 0)
		return keyword_read;
	else if (strcmp(buffer, "write") == 0)
		return keyword_write;
	else if (strcmp(buffer, "def") == 0)
		return keyword_def;
	else if (strcmp(buffer, "return") == 0)
		return keyword_return;
	else if (strcmp(buffer, "main") == 0)
		return -1;
	else if (strcmp(buffer, "null") == 0)
		return -1;
	else
		return identifier;
}

void print_lexeme_list(lexeme *list, int list_end)
{
	int i;
	printf("Lexeme List: \n");
	printf("lexeme\t\ttoken type\n");
	for (i = 0; i < list_end; i++)
	{
		// not an error
		if (list[i].type != -1)
		{
			switch (list[i].type)
			{
				case identifier :
					printf("%11s\t%d\n", list[i].identifier_name, identifier);
					break;
				case number :
					printf("%11d\t%d\n", list[i].number_value, number);
					break;
				case keyword_const :
					printf("%11s\t%d\n", "const", keyword_const);
					break;
				case keyword_var :
					printf("%11s\t%d\n", "var", keyword_var);
					break;
				case keyword_procedure :
					printf("%11s\t%d\n", "procedure", keyword_procedure);
					break;
				case keyword_call :
					printf("%11s\t%d\n", "call", keyword_call);
					break;
				case keyword_begin :
					printf("%11s\t%d\n", "begin", keyword_begin);
					break;
				case keyword_end :
					printf("%11s\t%d\n", "end", keyword_end);
					break;
				case keyword_if :
					printf("%11s\t%d\n", "if", keyword_if);
					break;
				case keyword_then :
					printf("%11s\t%d\n", "then", keyword_then);
					break;
				case keyword_while :
					printf("%11s\t%d\n", "while", keyword_while);
					break;
				case keyword_do :
					printf("%11s\t%d\n", "do", keyword_do);
					break;
				case keyword_read :
					printf("%11s\t%d\n", "read", keyword_read);
					break;
				case keyword_write :
					printf("%11s\t%d\n", "write", keyword_write);
					break;
				case keyword_def :
					printf("%11s\t%d\n", "def", keyword_def);
					break;
				case keyword_return :
					printf("%11s\t%d\n", "return", keyword_return);
					break;
				case period :
					printf("%11s\t%d\n", ".", period);
					break;
				case assignment_symbol :
					printf("%11s\t%d\n", ":=", assignment_symbol);
					break;
				case minus :
					printf("%11s\t%d\n", "-", minus);
					break;
				case semicolon :
					printf("%11s\t%d\n", ";", semicolon);
					break;
				case left_curly_brace :
					printf("%11s\t%d\n", "{", left_curly_brace);
					break;
				case right_curly_brace :
					printf("%11s\t%d\n", "}", right_curly_brace);
					break;
				case equal_to :
					printf("%11s\t%d\n", "==", equal_to);
					break;
				case not_equal_to :
					printf("%11s\t%d\n", "!=", not_equal_to);
					break;
				case less_than :
					printf("%11s\t%d\n", "<", less_than);
					break;
				case less_than_or_equal_to :
					printf("%11s\t%d\n", "<=", less_than_or_equal_to);
					break;
				case greater_than :
					printf("%11s\t%d\n", ">", greater_than);
					break;
				case greater_than_or_equal_to :
					printf("%11s\t%d\n", ">=", greater_than_or_equal_to);
					break;
				case plus :
					printf("%11s\t%d\n", "+", plus);
					break;
				case times :
					printf("%11s\t%d\n", "*", times);
					break;
				case division :
					printf("%11s\t%d\n", "/", division);
					break;
				case left_parenthesis :
					printf("%11s\t%d\n", "(", left_parenthesis);
					break;
				case right_parenthesis :
					printf("%11s\t%d\n", ")", right_parenthesis);
					break;
				default :
					printf("Implementation Error: unrecognized token type\n");
					break;
			}
		}
		// errors
		else
		{
			switch (list[i].error_type)
			{
				case ERR_IDENT_LENGTH :
					printf("Lexical Analyzer Error: maximum identifier length is 11\n");
					break;
				case ERR_NUM_LENGTH :
					printf("Lexical Analyzer Error: maximum number length is 5\n");
					break;
				case ERR_INVALID_IDENT :
					printf("Lexical Analyzer Error: identifiers cannot begin with digits\n");
					break;
				case ERR_INVALID_SYMBOL :
					printf("Lexical Analyzer Error: invalid symol\n");
					break;
				case ERR_INVALID_IDENT_NAME :
					printf("Lexical Analyzer Error: identifiers cannot be named 'null' or 'main'\n");
					break;
				default :
					printf("Implementation Error: unrecognized error type\n");
					break;
			}
		}
	}
	printf("\n");
}