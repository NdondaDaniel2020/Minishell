/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_file_name_util.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	space_before_string(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == '\'') || (str[i] == '"'))
		i++;
	if (str[i] == ' ')
		return (true);
	return (false);
}

bool	space_after_string(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len > 1 && ((str[len] == '\'') || (str[len] == '"')))
		len--;
	if (str[len] == ' ')
		return (true);
	return (false);
}

int	star_alpha(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == '\'') || (str[i] == '"'))
		i++;
	return (i);
}

bool	condition_adjust(int i, char **new_content)
{
	return ((count_chr('"', new_content[i]) > 0
			&& count_chr('\'', new_content[i]) > 0)
		|| (((count_chr('\'', new_content[i]) > 0
					&& count_chr('"', new_content[i]) == 0)
				|| (count_chr('"', new_content[i]) > 0
					&& count_chr('\'', new_content[i]) == 0))
			&& (space_before_string(new_content[i]) == false
				&& space_after_string(new_content[i]) == false))
		|| (count_chr('\'', new_content[i]) > 0
			&& count_chr('"', new_content[i]) == 0
			&& count_chr('\'', (new_content[i]
					+ star_alpha(new_content[i]))) % 2 != 0)
		|| (count_chr('"', new_content[i]) > 0
			&& count_chr('\'', new_content[i]) == 0
			&& count_chr('"', (new_content[i]
					+ star_alpha(new_content[i]))) % 2 != 0));
}

char	*strdelchr(char *str, char chr)
{
	int		i;
	int		coun_chr;
	char	*new_str;

	i = 0;
	coun_chr = count_chr(chr, str);
	new_str = (char *)ft_calloc((ft_strlen(str) - coun_chr) + 1, sizeof(char));
	while (*str)
	{
		if (*str != chr)
			new_str[i++] = *str;
		str++;
	}
	return (new_str);
}
