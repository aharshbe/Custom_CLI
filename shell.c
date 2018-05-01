#include "header.h"

int main(int argc, char **argv)
{

	char *user_input = NULL, **args;
	unsigned int status = 0;
	int child = 0;

	(void)argc;
	(void)argv;

	/* Infinitely get user input */
	while ((user_input = gen_input()))
	{	
		/* Check for builtins */
		if ((status = check_builtins(user_input)))
		{
			free(user_input);
			continue;
		}
		else
		{
			/* Create secondary 
			child process for execve */
			if (!(fork()))
			{
				args = tokenize(user_input);
				execute(args);
				free(user_input);
			}
			else
			{
				/* Parent process that is 
				waiting for child to finish */
				free(user_input);
				wait(&child);
			}
		}
	}
	/* Call exit wrapper */
	exit_CLI(user_input);
}
