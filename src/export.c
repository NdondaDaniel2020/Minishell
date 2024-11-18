/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_order(t_data *data)
{
	int 	i1;
	int 	i2;
	char	alpha;

	i1 = 0;
	alpha = 'a';
	while (i1 < 26)
	{
		i2 = 0;
		while (data->envp[i2])
		{
			if (data->envp[i2][0] == alpha || data->envp[i2][0] == alpha - 32)
				ft_printf("declare -x %s\n", data->envp[i2]);
			i2++;
		}
		alpha++;
		i1++;
	}
	i2 = 0;
	while (data->envp[i2])
	{
		if (ft_isalpha(data->envp[i2][0]) == 0)
			ft_printf("declare -x %s\n", data->envp[i2]);
		i2++;
	}
}

void	export(t_data *data)
{
	int		i1;
	int		i2;
	t_btree	*aux;

	i1 = 0;
	aux = data->btree;
	while (aux->content[i1])
		i1++;
	if (!ft_strncmp(aux->content[i1 - 1], "export",
		ft_strlen(aux->content[i1 - 1])))
	{
		print_env_order(data);
		return ;
	}
	i1 = 0;
	while (aux->content[i1])
	{
		if (!ft_isalpha(aux->content[i1][0]) && aux->content[i1][0] != '-')
		{
			ft_printf("export: `%s': not a valid identifier\n", aux->content[i1]);
		}
		else
		{
			i2 = 0;
			while (aux->content[i1][i2])
			{
				if (aux->content[i1][i2] ==  '=')
				{
					ft_printf("export: `=': not a valid identifier\n");
					break ;
				}
				if (!ft_isalnum(aux->content[i1][i2]) && aux->content[i1][i2] !=  '_')
				{
					ft_printf("export: not an identifier: %s\n", aux->content[i1]);
					break ;
				}
				ft_putchar_fd(aux->content[i1][i2], 1);
				i2++;
			}
			i1++;
		}

	}
	ft_putchar_fd('\n', 1);
}
