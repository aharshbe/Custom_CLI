#include "header.h"

int main(void)
{

	char *user_input = NULL;
	unsigned int status = 0;

	while (1)
	{
		/* Get user input */
		user_input = gen_input();
		status = check_builtins(user_input);
		
		if (status)
		{
			printf("built-in found\n");
			free(user_input);
			continue;
		}
		else
		{
			printf("built-in not found\n");
			free(user_input);
		}
	}
	exit_CLI(user_input);
}
