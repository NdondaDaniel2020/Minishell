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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Definições externas das funções e da estrutura global
typedef struct s_signal {
    int sigint;
    int sigquit;
    int pid;
    int exit_status;
} t_signal;

t_signal g_sig;


int		ft_nbrlen(long n)
{
	int		size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

int		ft_power(int nbr, int pow)
{
	int	res;

	if (pow == 0)
		return (1);
	res = nbr;
	while (pow > 1)
	{
		res *= nbr;
		pow--;
	}
	return (res);
}

char		*ft_itoa(int n)
{
	long	nbr;
	char	*s;
	int		div;
	int		i;

	i = 0;
	nbr = n;
	if (!(s = malloc(sizeof(char) * (ft_nbrlen(nbr) + 1))))
		return (NULL);
	if (nbr < 0)
	{
		s[i++] = '-';
		nbr = -nbr;
	}
	div = ft_power(10, ft_nbrlen(nbr) - 1);
	while (div > 0)
	{
		s[i++] = nbr / div + '0';
		nbr = nbr % div;
		div = div / 10;
	}
	s[i] = '\0';
	return (s);
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd("minishell>cx", STDERR_FILENO);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putendl_fd(nbr, STDERR_FILENO);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
	ft_memdel(nbr);
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

void setup_signal_handlers(void)
{
    struct sigaction sa;

    // Configura manipulador para SIGINT
    sa.sa_handler = sig_int;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    // Configura manipulador para SIGQUIT
    sa.sa_handler = sig_quit;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa, NULL);
}

int main(void)
{
    char *line;

    // Inicializa a estrutura global e os manipuladores de sinais
    sig_init();
    setup_signal_handlers();

    while (1)
    {
        // Exibe o prompt
        write(STDOUT_FILENO, "minishell>", 11);

        // Lê entrada do usuário
        line = NULL;
        size_t len = 0;
        if (getline(&line, &len, stdin) == -1)
        {
            free(line);
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        // Simulação: apenas imprime a linha e define o status de saída como 0
        write(STDOUT_FILENO, "Executando comando: ", 21);
        write(STDOUT_FILENO, line, len);
        g_sig.exit_status = 0;

        free(line);
    }

    return g_sig.exit_status;
}

