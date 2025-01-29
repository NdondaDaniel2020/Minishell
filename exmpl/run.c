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

bool is_heredoc_redirection(char *str)
{
	int i = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<')
			&& (str[i - 1] != '>' && str[i - 1] != '<')
			&& (str[i + 2] != '>' && str[i + 2] != '<' && str[i + 2] != '\0')
			&& (str[i + 2] == ' ' && str[i + 3] != ' ' && str[i + 3] != '\0'))
			return (true);
		i++;
	}
	return (false);
}

int	main(void)
{
	ft_printf("{{%i}}\n", is_heredoc_redirection("ls <<a"));
    return (0);
}
