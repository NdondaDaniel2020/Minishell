/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	environment_variation_expansion_in_heredoc(char **line, t_data *data)
{
		int		old_size;
		int		new_size;
		char	*value_env;

		value_env = get_environment_variation_expansion((*line), data);
		old_size = ft_strlen((*line));
		new_size = ft_strlen(value_env);
		(*line) = ft_realloc((*line), old_size, new_size + 1);
		ft_strlcpy((*line), value_env, new_size + 1);
		free(value_env);
}

void	put_warning(int line, char *delimiter)
{
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}
