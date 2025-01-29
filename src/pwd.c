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

int	pwd(t_new_list *aux, t_data *data)
{
	char	*cwd;

	cwd = ft_calloc(5048, sizeof(char));
	if (!cwd)
		return (change_environment_variables_question_mark(2, data));
	getcwd(cwd, 5048);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (change_environment_variables_question_mark(0, data));
}
