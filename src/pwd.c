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

void	pwd(t_data *data)
{
	char *cwd;

	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
		data->output = NULL;
	if (getcwd(cwd, 5048) == NULL)
	{
		free(cwd);
		data->output = NULL;
	}
	ft_printf("%s\n", cwd);
	data->output = cwd;
}
