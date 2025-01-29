/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ctrl_c_heredoc_pipe(char *join, char *line, t_data *data)
{
	if (join != NULL)
		free(join);
	return (free_all_data(data), free(line), NULL);
}

bool	last_pipe(char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (len > -1 && line[len] && (line[len] == ' ' || line[len] == '|'))
	{
		if (line[len] == '|')
			return (true);
		len--;
	}
	return (false);
}

bool	first_pipe(char *join, char *line, t_data *data)
{
	int		i;
	char	*aux_chr;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '|'))
	{
		if (line[i] == '|')
		{
			join_lines_pipe(&join, line);
			aux_chr = ft_strjoin_free(ft_strdup(data->command), join);
			add_history(aux_chr);
			free(aux_chr);
			free(join);
			ft_putstr("syntax error near unexpected token `", 2);
			ft_putstr("|", 2);
			ft_putstr("'\n", 2);
			free_all_data(data);
			return (true);
		}
		i++;
	}
	return (false);
}

void	syntax_error_unexpected(char *line, char *join, t_data *data)
{
	ft_putstr_fd("syntax error: unexpected end of file\n",
		STDERR_FILENO);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_data(data);
	free(line);
	free(join);
	exit(2);
}

void	add_matrix_in_newlist(t_data *data, char **matrix)
{
	t_new_list	*aux;

	aux = data->list;
	while (aux)
	{
		if (len_matrix(aux->content) == 0)
		{
			free_matrix(aux->content);
			aux->content = matrix;
			return ;
		}
		aux = aux->next;
	}
	ft_lstnew_addback(&data->list, ft_lstnew_new(matrix));
}
