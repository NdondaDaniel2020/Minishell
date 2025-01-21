/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_lines(char **join, char *line)
{
	if ((*join) == NULL)
		(*join) = ft_strdup(line);
	else
	{
		(*join) = ft_strjoin_free((*join), line);
		(*join) = ft_strjoin_free((*join), "\n");
	}
}

char	*handle_heredoc_input_quotes(t_data *data, char delimiter)
{
	char	*line;
	char	*join;

	join = NULL;
	while (1)
	{
		line = readline("> ");
		if (g_satatus == 1)
			return (free(line), NULL);
		if (line == NULL)
		{
			ft_putstr_fd("unexpected EOF while looking for matching `", 2);
			ft_putchar_fd(delimiter, 2);
			ft_putstr_fd("'\n", 2);
			free_data(data);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit(2);
		}
		join_lines(&join, line);
		if (!line || ft_strchr(line, delimiter))
			break ;
		free(line);
	}
	free(line);
	return (join);
}

bool	heredoc_quotes(t_data *data, char **command)
{
	int		old_size;
	int		new_size;
	char	*join;
	char	*new_command;

	new_command = handle_heredoc_input_quotes(data,
			character_of_unclosed_quotes(*command));
	if (new_command == NULL)
		return (false);
	join = ft_strjoin(*command, new_command);
	old_size = ft_strlen(*command);
	new_size = ft_strlen(join);
	(*command) = ft_realloc((*command), old_size, new_size + 1);
	ft_strlcpy((*command), join, new_size + 1);
	add_history(join);
	free(join);
	return (true);
}
