#include "header.h"

/* Show prompt function */
void print_prompt(void)
{
	write(1, PROMPT, strlen(PROMPT));
}

/**
* Check for built-ins
* @command: command to check
* Return: 1 if a built-in was found, 0 if not
**/
int check_builtins(char *command)
{
	/* Create struct of builtins */
	cmds builtins[] = {
		{"exit", exit_CLI},
		{"history", history},
		{"clear", clear},
		{"c", clear},
		{"env", NULL},
		{"unset", NULL}, 
		{"set", NULL},
		{"help", help},
		{"alias", NULL},
		{NULL, NULL}
	};

	/* Look through builtins for possible command */
	for (int i = 0; builtins[i].command; i++)
	{
		if (strcmp(builtins[i].command, command) == 0)
		{
			builtins[i].f(command);
			return (1);
		}
	}
	return (0);
}

/* Execve function */
void execute(char **args)
{
	printf("executed\n");
	free(args);
}

/* Tokenize function */
char **tokenize(char *buffer)
{
	char *token = NULL, *save, **args;
	const char *delim = " \n";
	int i, j = 0;

	args = malloc(BUFF);
	if (!args)
		printf("malloc error\n");

	/** 
	* Making a copy of buffer 
	* because strtok will kill it 
	**/
	save = buffer;
	(void)save;

	token = strtok(buffer, delim);
	for (i = 0; token; i++)
	{
		args[i] = token;
		token = strtok(NULL, delim);
	}

	for ( j = 0; j <= i; j++, i--)
		printf("token[%d] = %s\n", j, args[j]);

	return (args);
}


/* Get input function */
char *gen_input(void)
{
	char *user_input = NULL;
	size_t input_len = 0;

	/* Display prompt */
	print_prompt(); 

	/* Get user input and remove new line */
	getline(&user_input, &input_len, stdin);
	user_input[strlen(user_input) - 1] = '\0';

	return (user_input);
}

/* Exit CLI: free buffer and exit program */
void exit_CLI(char *buffer)
{
	free(buffer);
	exit (0);
}

/* Print CLI history */
void history(char *buffer)
{
	(void)buffer;
	printf("history\n");
}

/* Clears the screen */
void clear(char *buffer)
{
	(void)buffer;
	system("@cls||clear");
}

void help(char *buffer)
{
	(void)buffer;
	printf("help\n");
}

