/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
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
	int		j;
	char	alpha;

	alpha = 64;
	while (alpha < 125)
	{
		j = 0;
		while (data->envp[j])
		{
			if (data->envp[j][0] == alpha && !ft_strchr(data->envp[j], '?'))
				ft_printf("declare -x %s\n", data->envp[j]);
			j++;
		}
		alpha++;
	}
}

bool	print_export(t_data *data)
{
	int			i1;
	t_new_list	*aux;

	i1 = 0;
	aux = data->list;
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

static void	check_character(int i1, bool *add_var, t_new_list *aux)
{
	int	i2;

	i2 = 0;
	while (aux->content[i1][i2])
	{
		if (aux->content[i1][i2] == '=' && ft_strlen(aux->content[i1]) == 1)
		{
			write(2, "export: `=': not a valid identifier\n", 36);
			*add_var = false;
			write(2, "\n", 1);
			break ;
		}
		if (!ft_isalnum(aux->content[i1][i2])
			&& !is_valid_char(aux->content[i1][i2]))
		{
			write(2, "export: not an identifier: ", 27);
			ft_putstr_fd(aux->content[i1], 2);
			write(2, "\n", 1);
			*add_var = false;
			break ;
		}
		i2++;
	}
}

bool	check_error(int i1, t_new_list *aux)
{
	bool	add_var;

	add_var = true;
	if (!ft_isalpha(aux->content[i1][0]) && aux->content[i1][0] != '_')
	{
		write(2, "export: `", 9);
		ft_putstr_fd(aux->content[i1], 2);
		write(2, "': not a valid identifier\n", 26);
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
