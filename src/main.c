#include "minishell.h"

void	execute_command(char *command)
{
	//
}

int main(void)
{
	char *input;

    while (1)
	{
		input = readline("TeamWork> ");
        add_history(input);
        // printf("%s\n", input);
        free(input);
    }
    return 0;
}