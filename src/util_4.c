/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	change_value_in_adjust_filename(int i, bool *valid, t_new_list *aux)
{
	char	*aux_aux;

	aux_aux = ft_strdup(aux->content[i]);
	aux->content[i] = adjust_file_name(aux->content[i]);
	if (aux->content[i] == NULL)
	{
		aux->content[i] = aux_aux;
		return (true);
	}
	free(aux_aux);
	(*valid) = false;
	return (false);
}

static bool	error_filename_syntax(int i, t_new_list *aux)
{
	if (ft_strlen(aux->content[i]) == 0)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		return (true);
	}
	else if (is_directory_valid(aux->content[i]))
	{
		ft_putstr_fd(aux->content[i], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (true);
	}
	else if ((i + 1) < len_matrix(aux->content)
		&& (all_char_equal_char(aux->content[i + 1], '"')
			|| all_char_equal_char(aux->content[i + 1], '\'')))
	{
		ft_putstr_fd(": command not found\n", 2);
		return (true);
	}
	return (false);
}

bool	adjust_filename_in_redirection_syntax(t_new_list *aux)
{
	int		i;
	bool	valid;

	i = 0;
	valid = false;
	while (aux->content[i])
	{
		if (valid)
		{
			if (change_value_in_adjust_filename(i, &valid, aux))
				return (true);
			if (error_filename_syntax(i, aux))
				return (true);
		}
		if (valid_string_condition_for_redirection(aux->content[i]))
			valid = true;
		i++;
	}
	return (false);
}

void	null_string(char ***matrix)
{
	int	i;

	i = 0;
	while ((*matrix)[i])
	{
		if (ft_strlen((*matrix)[i]) == 0)
			(*matrix)[i] = NULL;
		i++;
	}
}

void	matrix_space_position_adjustment(char ***matrix)
{
	int		i;
	int		len_m;
	char	*aux;

	if (ft_strlen((*matrix)[0]) == 0)
	{
		i = 0;
		len_m = len_matrix(*matrix);
		aux = (*matrix)[0];
		while (i < len_m - 1)
		{
			(*matrix)[i] = (*matrix)[i + 1];
			i++;
		}
		(*matrix)[i] = aux;
	}
}
