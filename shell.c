#include "header.h"

int main(void)
{

	char *user_input = NULL;
	unsigned int status = 0;

	/* Infinitely get user input */
	while ((user_input = gen_input()))
	{	
		if ((status = check_builtins(user_input)))
		{
			printf("built-in found\n");
			free(user_input);
			continue;
		}
		else
		{
			printf("built-in not found\n");
			tokenize(user_input);
			free(user_input);
		}
	}
	/* Call exit wrapper */
	exit_CLI(user_input);
}
