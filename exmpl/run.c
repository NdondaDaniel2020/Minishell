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


static int	get_shlvl_value(const char *shlvl_str)
{
	size_t	prefix_len;

	prefix_len = 6;
	if (strncmp(shlvl_str, "SHLVL=", prefix_len) != 0)
		return (-1);
	return (atoi(shlvl_str + prefix_len));
}

static void	int_to_str(int num, char *buffer)
{
	int	len;
	int	temp;

	len = 0;
	temp = num;
	while (temp > 0)
	{
		len++;
		temp /= 10;
	}
	if (num == 0)
		len = 1;
	buffer[len] = '\0';
	while (len > 0)
	{
		buffer[--len] = (num % 10) + '0';
		num /= 10;
	}
}

static char	*increment_shlv(char *shlvl_str)
{
	int		shlvl;
	char	*new_shlvl_str;
	char	shlvl_str_value[12];
	size_t	prefix_len;
	size_t	new_str_len;

	prefix_len = 6;
	shlvl = get_shlvl_value(shlvl_str);
	if (shlvl == -1)
		return (NULL);
	shlvl++;
	int_to_str(shlvl, shlvl_str_value);
	new_str_len = prefix_len + strlen(shlvl_str_value) + 1;
	new_shlvl_str = (char *)malloc(new_str_len);
	if (new_shlvl_str == NULL)
		return (NULL);
	ft_strlcpy(new_shlvl_str, "SHLVL=", 7);
	ft_strlcat(new_shlvl_str, shlvl_str_value,
		ft_strlen(new_shlvl_str) + ft_strlen(new_shlvl_str) + 1);
	free(shlvl_str);
	return (new_shlvl_str);
}

static char	**list_environment(void)
{
	static char	*env[] = {"SYSTEMD_EXEC_PID", "SSH_AUTH_SOCK",
		"SESSION_MANAGER", "GNOME_TERMINAL_SCREEN", "LANG",
		"XDG_CURRENT_DESKTOP", "XDG_GREETER_DATA_DIR", "LIBVIRT_DEFAULT_URI",
		"GPG_AGENT_INFO", "DESKTOP_SESSION", "QT_IM_MODULE", "XDG_MENU_PREFIX",
		"XDG_SESSION_PATH", "USER", "DBUS_SESSION_BUS_ADDRESS", "DOCKER_HOST",
		"SSH_AGENT_LAUNCHER", "GTK_MODULES", "XDG_CONFIG_DIRS",
		"GTK_IM_MODULE", "XDG_SESSION_DESKTOP", "QT_ACCESSIBILITY",
		"GNOME_DESKTOP_SESSION_ID", "KRB5CCNAME", "LOGNAME",
		"GNOME_TERMINAL_SERVICE", "VTE_VERSION", "PATH", "XDG_RUNTIME_DIR",
		"XDG_DATA_DIRS", "XDG_SEAT_PATH", "SHELL", "XMODIFIERS",
		"XDG_SESSION_TYPE", "HOME", "COLORTERM", "XAUTHORITY", "PWD",
		"XDG_SESSION_CLASS", "TERM", "GDMSESSION", "DISPLAY", "SHLVL",
		"OLDPWD", "_", "?=0", NULL};

	return (env);
}

char	**get_all_environment(char **envp)
{
	int		i;
	char	*env;
	char	**new_env;

	i = len_matrix(envp);
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		env = ft_strdup(envp[i]);
		if (!ft_strncmp(env, "SHLVL", ft_strlen(env) - 2))
			env = increment_shlv(env);
		new_env[i] = env;
		i++;
	}
	return (new_env);
}

int main(int ac, char **av, char **env)
{
	char **new_env;

	new_env = get_all_environment(envp);
	while (*new_env)
	{
		ft_printf("[%s]\n", *new_env);
		new_env++;
	}
}
