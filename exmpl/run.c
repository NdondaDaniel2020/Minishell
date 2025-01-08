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

// Definições externas das funções e da estrutura global

int	g_exit_status;

void	sig_int(int code)
{
}

void	sig_quit(int code)
{
}

void	sig_init(void)
{
}

void setup_signal_handlers(void)
{
    struct sigaction sa;

    // Configura manipulador para SIGINT control + c
    sa.sa_handler = sig_int;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL); 

    // Configura manipulador para SIGQUIT control + \
    sa.sa_handler = sig_quit;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa, NULL);
}

int	main(void)
{
	// t_data	data;
	char	*input;

	setup_signal_handlers();
	// init_data(&data);
	// data.envp = get_all_environment();
	// data.path = ft_split(get_env("PATH", &data), ':');
	while (1)
	{
		input = readline("TeamWork> ");
		if (input[0] != '\0')
		{
			add_history(input);
			// master(input, &data);
			free(input);
		}
	}
	return (0);
}
