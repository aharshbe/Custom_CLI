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
		{"env", env},
		{"unset", NULL}, 
		{"set", NULL},
		{"help", help},
		{"alias", NULL},
		{"cd", NULL},
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
	extern char **environ;
	char *path = getenv("PATH"), *sub_token = NULL, *command;
	const char *delim = ":";
	int i, status = 0;
	path_p list[BUFF];


	/**
	* Create a token of the path ':'' delimeted 
	* and add to 'path_p' struct
	*/
	sub_token = strtok(path, delim);
	for (i = 0; sub_token; i++)
	{
		list[i].abs = sub_token;
		sub_token = strtok(NULL, delim);
	}
	/**
	* Concatinate the path token and the command
	* to generate the execve arguement to execute
	*/
	for (int j = 0; j < i; j++)
	{
		command = strcat_slash(list[j].abs, args[0]);
		status = access(command, F_OK);

		if (!status)
			execve(command, args, environ);
	}
	free(command);
	free(args);
	exit(0);
}

/* Tokenize function */
char **tokenize(char *buffer)
{
	char *token = NULL, **args;
	const char *delim = " \n";
	int i;

	args = malloc(BUFF);
	if (!args)
		printf("malloc error\n");

	token = strtok(buffer, delim);
	for (i = 0; token; i++)
	{
		args[i] = token;
		token = strtok(NULL, delim);
	}
	args[i] = NULL;

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

/* Prints environment variables */
void env(char *buffer)
{
	extern char **environ;
	(void)buffer;

	for (int i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
}

char *strcat_slash(char *dest, char *src)
{
	int size = 0, size2 = 0, j = 0, k = 0, total = 0;
	char *final;

	while (dest[size])
		size++;

	while (src[size2])
		size2++;

	final = malloc(total = size + size2 + 2);
	if (!final)
		perror("final");

	while (dest[j])
	{
		final[j] = dest[j];
		j++;
	}
	final[j++] = '/';

	for (k = 0; j < total; j++, k++)
		final[j] = src[k];

	return (final);
}

