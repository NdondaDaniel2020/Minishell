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

/* CTRL-C */
void	handle_sigint(int sig)
{
	(void)sig;
	write (STDOUT_FILENO, "\nTeamWork> ", 12);
}

/* CTRL-\ */
void	setup_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
