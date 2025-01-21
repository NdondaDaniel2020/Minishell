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

static char	*handle_heredoc_input(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_satatus == 1)
			return (free_all_data(data), free(line), NULL);
		if (line == NULL)
		{
			ft_putstr_fd("syntax error: unexpected end of file\n",
				STDERR_FILENO);
			free_data(data);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit(2);
		}
		if (line && all_is_space(line) == false
			&& (ft_strchr(line, '$')
				|| ft_strchr(line, '\'')
				|| ft_strchr(line, '"')))
			environment_variation_expansion_in_heredoc(&line, data);
		if (line && all_is_space(line) == false)
			return (line);
		free(line);
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

bool	heredoc_pipe_fork(t_data *data)
{
	char		*new_line;
	char		*aux_chr;
	char		**matrix;

	new_line = handle_heredoc_input(data);
	if (new_line == NULL)
		return (false);
	aux_chr = ft_strjoin(data->command, new_line);
	add_history(aux_chr);
	matrix = split_2(new_line, ' ');
	matrix_space_position_adjustment(&matrix);
	null_string(&matrix);
	free(new_line);
	free(aux_chr);
	add_matrix_in_newlist(data, matrix);
	return (true);
}
