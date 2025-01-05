/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_pwd(t_new_list *aux)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (aux->content[i])
	{
		if (ft_strlen(aux->content[i]) == 0)
		{
			i++;
			continue ;
		}
		if (len > 0 && ft_strlen(aux->content[i]) > 0)
		{
			write(2, "pwd: too many arguments\n", 24);
			return (true);
		}
		i++;
		len++;
	}
	return (false);
}

int	pwd(t_new_list *aux, t_data *data)
{
	char	*cwd;

	if (error_pwd(aux))
		return (change_environment_variables_question_mark(1, data));
	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
		return (change_environment_variables_question_mark(2, data));
	getcwd(cwd, 5048);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (change_environment_variables_question_mark(0, data));
}
