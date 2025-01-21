/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:26 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:04:37 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <stdbool.h>
#include <stdio.h>

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

int	main(void)
{
    return (0);
}
