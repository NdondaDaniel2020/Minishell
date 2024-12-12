/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_environment_variables_question_mark(int value, t_data *data)
{
	int		i;
	int		len;
	char	*new_env;
	char	*value_str;

	i = 0;
	while (data->envp[i])
		i++;
	if (ft_atoi(data->envp[i - 1] + 2) != value)
	{
		len = ft_nblen(value, 10);
		new_env = ft_calloc(3 + len, sizeof(char));
		if (!new_env)
			return ;
		ft_strlcpy(new_env, "?=", 3);
		value_str = ft_itoa(value);
		new_env = ft_strjoin_free(new_env, value_str);
		free(data->envp[i - 1]);
		data->envp[i - 1] = new_env;
		free(value_str);
	}
}

void	export(t_new_list *aux, t_data *data)
{
	int			i1;
	bool		add_var;

	i1 = 1;
	if (print_export(data))
		return ;
	while (aux->content[i1])
	{
		add_var = check_error(i1, aux);
		if (add_var)
			add_environment_variable(aux->content[i1], data);
		else
			change_environment_variables_question_mark(1, data);
		i1++;
	}
	if (get_env("PATH", data) && data->path == NULL)
		data->path = ft_split(get_env("PATH", data), ':');
}
