/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	all_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool	is_pipe_heredoc(char *command)
{
	int	len;

	len = ft_strlen(command);
	if (command[len - 1] == '|')
		return (true);
	while (len > 0 && command[len - 1] == ' ' )
		len--;
	if (command[len - 1] == '|')
		return (true);
	else
		return (false);
}

bool	has_unclosed_quotes(const char *str)
{
	int		i;
	int		save;
	char	chr;

	i = 0;
	save = -1;
	chr = '\0';
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"') && chr == '\0')
		{
			chr = str[i];
			save = i;
		}
		else if (chr != '\0' && str[i] == chr && save != i)
		{
			chr = '\0';
			save = -1;
		}
		i++;
	}
	if (chr != '\0')
		return (true);
	return (false);
}

char	character_of_unclosed_quotes(const char *str)
{
    int		i;
	int		save;
	char	chr;

    i = 0;
	save = -1;
	chr = '\0';
    while (str[i] != '\0')
    {
		if ((str[i] == '\'' || str[i] == '\"') && chr == '\0')
		{
			chr = str[i];
			save = i;
		}
		else if (chr != '\0' && str[i] == chr && save != i)
		{
			chr = '\0';
			save = -1;
		}
        i++;
    }
	return (chr);
}
