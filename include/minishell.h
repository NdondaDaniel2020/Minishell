#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <readline/history.h>
#include <readline/readline.h>

char	*get_argument(char *command);
char	*get_command(char *command);

#endif