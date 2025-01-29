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

void	join_lines_pipe(char **join, char *line)
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
			return (ctrl_c_heredoc_pipe(join, line, data));
		if (line == NULL)
			syntax_error_unexpected(line, join, data);
		if (first_pipe(join, line, data))
			return (NULL);
		if (line && all_is_space(line) == false && (ft_strchr(line, '$')
				|| ft_strchr(line, '\'') || ft_strchr(line, '"')))
			environment_variation_expansion_in_heredoc(&line, data);
		las_pipe = last_pipe(line);
		join_lines_pipe(&join, line);
		if (join && las_pipe == false && all_is_space(join) == false)
			return (join);
	}
}

bool	heredoc_pipe(t_data *data)
{
	int			i;
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
	return (free(aux_chr), free_matrix(matrix_pipe), true);
}
