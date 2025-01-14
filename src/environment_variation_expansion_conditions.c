/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variation_expansion_conditions.c       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:26 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:04:37 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*invert_str(char *str)
{
	int		i;
	int		len;
	char	*new_string;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	new_string = ft_calloc(len + 1, sizeof(char));
	while (str[i])
		new_string[len-- - 1] = str[i++];
	return (new_string);
}

bool	condition_put_env_quotes(char *str, char *sub)
{
	return (first_str('\'', str) && (count_chr('\'', sub) % 2 != 0)
		&& (count_chr('"', sub) > 0));
}

bool	condition_extract_value_env_quotes(char *str, char *sub)
{
	return (first_str('"', str) && (count_chr('"', sub) % 2 != 0)
		&& (count_chr('\'', sub) > 0));
}

bool	condition_put_env_environment(char *str, char *sub)
{
	return ((count_chr('"', str) == 0 && (count_chr('\'', sub) % 2 != 0))
		 || (first_str('"', str) && (count_chr('"', sub) % 2 == 0)
		 		&& (count_chr('\'', sub) > 0)));
}

bool	condition_extract_value_env(char *str, char *sub)
{
	return ((count_chr('"', sub) == 0 && count_chr('\'', sub) == 0)
		 || (count_chr('\'', sub) == 0 && (count_chr('"', sub) > 0))
		 || (count_chr('"', sub) == 0 && (count_chr('\'', sub) % 2 == 0))
		 || (first_str('\'', str) && (count_chr('\'', sub) % 2 == 0)
		 	&& (count_chr('"', sub) > 0)));
}
