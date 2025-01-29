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

bool check_pipe_valid(char *command)
{
    int i;
	int len_pipe;

	i = 0;
	len_pipe = 0;
	while (command[i])
	{
		if (command[i] == '|')
			len_pipe++;
		if (command[i] != '|' && command[i] != ' ')
			len_pipe = 0;
		if (len_pipe > 1)
			return (true);
		i++;
	}
	return (false);
}

int	main(void)
{
	ft_printf("{{%i}}\n", check_pipe_valid("ls | wc |"));
    return (0);
}
