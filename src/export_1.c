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
}
