/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_comand_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_index_str(t_index_str *index_str)
{
	index_str->index = -1;
	index_str->str = NULL;
}

void	set_index_str(int index, char *str, t_index_str *index_str)
{
	index_str->index = index;
	index_str->str = str;
}

t_index_str	*chack_path_is_directory(int i,
				t_index_str	*index_str, t_new_list *aux, t_data *data)
{
	if (is_directory_valid(aux->content[i]))
	{
		ft_putstr_fd(aux->content[i], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		change_environment_variables_question_mark(126, data);
	}
	else
	{
		ft_putstr_fd(aux->content[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		change_environment_variables_question_mark(127, data);
	}
	init_index_str(index_str);
	return (index_str);
}

t_index_str	*get_absolute_path(int i, t_new_list *aux, t_data *data)
{
	char		*str;
	t_index_str	*index_str;

	index_str = ft_calloc(1, sizeof(t_index_str));
	init_index_str(index_str);
	if (ft_strnstr(aux->content[i], "/", ft_strlen(aux->content[i])))
	{
		if (aux->content[i][ft_strlen(aux->content[i]) - 1] == '/'
			|| is_other_file(aux->content[i]))
			return (chack_path_is_directory(i, index_str, aux, data));
		else
		{
			set_index_str(0, ft_strdup(aux->content[i]), index_str);
			return (index_str);
		}
	}
	else
	{
		str = get_valid_path(aux, data);
		if (str == NULL)
			set_index_str(-2, str, index_str);
		else
			set_index_str(0, str, index_str);
		return (index_str);
	}
}
