#ifndef _header_
#define _header_

/* Include headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Marcos */
#define PROMPT "--> "
#define BUFF 1024

/* Structs */
/**
* struct builtins: to keep builtins in one place
* @command: the command to execute
* @f: the corresponding function for the command
*/
typedef struct builtins {
	char *command;
	void (*f)(char *args);
} cmds;
/**
* struct path_parsed: store the path ':' delimited
* @abs: each path token
*/
typedef struct path_parsed {
	char *abs;
} path_p;

/* Functions */
void print_prompt(void);
char *gen_input(void);
int check_builtins(char *command);
void exit_CLI(char *buffer);
void history(char *buffer);
void clear(char *buffer);
char **tokenize(char *buffer);
void help(char *buffer);
void execute(char **args);
void env(char *buffer);
char *strcat_slash(char *dest, char *src);

#endif