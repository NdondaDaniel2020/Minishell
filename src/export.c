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
	int i2;

	i2 = 0;
	while (aux->content[i1][i2])
	{
		if (aux->content[i1][i2] ==  '=' && ft_strlen(aux->content[i1]) == 1)
		{
			ft_printf("export: `=': not a valid identifier\n");
			*add_var = false;
			break ;
		}
		if (!ft_isalnum(aux->content[i1][i2]) &&
			aux->content[i1][i2] !=  '_' &&
			aux->content[i1][i2] !=  '=')
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
	if (!ft_isalpha(aux->content[i1][0]) && aux->content[i1][0] != '-')
	{
		ft_printf("export: `%s': not a valid identifier\n", aux->content[i1]);
		add_var = false;
	}
	else
		check_character(i1, &add_var, aux);
	return (add_var);
}

void	add_environment_variable(char *env_var, t_data *data)
{
	// unique
	int		i;
	bool	unique;

	i = 0;
	unique = true;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], env_var, ft_strlen(env_var)))
			unique = false;
		i++;
	}
	if (unique)
	{
        data->envp = ft_realloc((void *)data->envp, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
        data->envp[i] = ft_strdup(env_var);
        data->envp[i + 1] = NULL;
		i = 0;
		while (data->envp[i])
		{
			ft_printf("[[%i] %s]\n", i, data->envp[i]);
			i++;
		}
		ft_printf("[[%i]] ", i);
	}
	// se ja existe e valo e diferente, alterar
}

void	export(t_data *data)
{
	int		i1;
	bool	add_var;
	t_btree	*aux;

	i1 = 1;
	aux = data->btree;
	if (print_export(data))
		return ;
	while (aux->content[i1])
	{
		add_var = check_error(i1, aux);
		if (add_var)
			add_environment_variable(aux->content[i1], data);
		i1++;
	}
	ft_putchar_fd('\n', 1);
}