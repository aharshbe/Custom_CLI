#ifndef _header_
#define _header_

/* Include files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

/* Defines */
#define PROMPT "--> "

/* Structs */
typedef struct builtins {
	char *command;
	void (*f)(char *args);
} cmds;

/* Functions */
void print_prompt(void);
char *gen_input(void);
int check_builtins(char *command);
void exit_CLI(char *buffer);
void history(char *buffer);
void clear(char *buffer);
void tokenize(char *buffer);
void help(char *buffer);

#endif