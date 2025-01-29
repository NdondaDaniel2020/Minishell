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

static void	join_lines_pipe(char **join, char *line)
{
	if ((*join) == NULL)
	{
		(*join) = ft_strdup(line);
		free(line);
	}
	else
	{
		(*join) = ft_strjoin_free((*join), line);
		free(line);
	}
}

static bool	last_pipe(char *line)
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

static char	*handle_heredoc_input(t_data *data)
{
	char	*line;
	char	*join;
	bool	las_pipe;

	join = NULL;
	while (1)
	{
		line = readline("> ");
		if (g_satatus == 2)
			return (free_all_data(data), free(line), NULL);
		if (line == NULL)
		{
			ft_putstr_fd("syntax error: unexpected end of file\n",
				STDERR_FILENO);
			free_data(data);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit(2);
		}
		if (line && all_is_space(line) == false && (ft_strchr(line, '$')
			|| ft_strchr(line, '\'') || ft_strchr(line, '"')))
			environment_variation_expansion_in_heredoc(&line, data);
		las_pipe = last_pipe(line);
		join_lines_pipe(&join, line);
		if (join && las_pipe == false && all_is_space(join) == false)
			return (join);
	}
}

static void	add_matrix_in_newlist(t_data *data, char **matrix)
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

bool	heredoc_pipe(t_data *data)
{
	int 		i;
	char		*new_line;
	char		*aux_chr;
	char		**matrix;
	char		**matrix_pipe;

	new_line = handle_heredoc_input(data);
	if (new_line == NULL)
		return (free_all_data(data), false);
	aux_chr = ft_strjoin(data->command, new_line);
	add_history(aux_chr);
	if (simple_error(aux_chr))
		return (free(aux_chr), free_all_data(data), false);
	matrix_pipe = split_2(new_line, '|');
	i = 0;
	while (matrix_pipe[i])
	{
		matrix = split_2(matrix_pipe[i], ' ');
		matrix_space_position_adjustment(&matrix);
		null_string(&matrix);
		add_matrix_in_newlist(data, matrix);
		i++;
	}
	free(aux_chr), free_matrix(matrix_pipe);
	return (true);
}
