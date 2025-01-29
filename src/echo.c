/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_new_list *aux, t_data *data)
{
	bool	no_newline;
	int		i;
	int		len;

	if (echo_is_empty(aux))
		return (change_environment_variables_question_mark(0, data));
	no_newline = false;
	i = 1;
	len = len_matrix(aux->content);
	while (i < len && ft_strncmp(aux->content[i], "-n", 2) == 0 && \
	only_valid_n(aux->content[i]))
	{
		no_newline = true;
		i++;
	}
	while (i < len)
	{
		ft_putstr_fd(aux->content[i], 1);
		if (++i < len)
			ft_putchar_fd(' ', 1);
	}
	if (!no_newline)
		ft_putchar_fd('\n', 1);
	return (change_environment_variables_question_mark(0, data));
}