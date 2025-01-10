/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:55:19 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/02 11:27:20 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////
static void clear_buffer(void)
{
	char	c;

	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
	}
}
static void	handle_sigint(int sig)
{
	(void)sig;
	clear_buffer();
	write (STDOUT_FILENO, "\nTeamWork> ", 12);
}

void	setup_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
/////



// static void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	write(STDOUT_FILENO, "\nTeamWork> ", 12);
// }

// void	setup_signal(void)
// {
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// }
