/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_order(t_data *data)
{
	int		i1;
	int		i2;
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

bool	print_export(t_data *data)
{
	int		i1;
	t_btree	*aux;

	i1 = 0;
	aux = data->btree;
	while (aux->content[i1])
		i1++;
	if (!ft_strncmp(aux->content[i1 - 1], "export",
			ft_strlen(aux->content[i1 - 1])))
	{
		print_env_order(data);
		return (true);
	}
	return (false);
}

static void	check_character(int i1, bool *add_var, t_btree *aux)
{
	int	i2;

	i2 = 0;
	while (aux->content[i1][i2])
	{
		if (aux->content[i1][i2] == '=' && ft_strlen(aux->content[i1]) == 1)
		{
			ft_printf("export: `=': not a valid identifier\n");
			*add_var = false;
			break ;
		}
		if (!ft_isalnum(aux->content[i1][i2])
			&& aux->content[i1][i2] != '_' && aux->content[i1][i2] != '='
			&& aux->content[i1][i2] != '\'' && aux->content[i1][i2] != '\"'
			&& aux->content[i1][i2] != '$' && aux->content[i1][i2] != '\\'
			&& aux->content[i1][i2] != ' ' && aux->content[i1][i2] != '.'
			&& aux->content[i1][i2] != '/' && aux->content[i1][i2] != ':')
		{
			ft_printf("export: not an identifier: %s\n", aux->content[i1]);
			*add_var = false;
			break ;
		}
		i2++;
	}
}

bool	check_error(int i1, t_btree *aux)
{
	bool	add_var;

	add_var = true;
	if (!ft_isalpha(aux->content[i1][0]) && aux->content[i1][0] != '_')
	{
		ft_printf("export: `%s': not a valid identifier\n", aux->content[i1]);
		add_var = false;
	}
	else
		check_character(i1, &add_var, aux);
	return (add_var);
}

int	ft_strnchrcmp(const char *s1, const char *s2, size_t n, char chr)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n) && s1[i] != chr)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
