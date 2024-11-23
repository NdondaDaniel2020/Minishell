/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**list_environment(void)
{
	static char	*env[] = {"SYSTEMD_EXEC_PID", "SSH_AUTH_SOCK",
		"SESSION_MANAGER", "GNOME_TERMINAL_SCREEN", "LANG",
		"XDG_CURRENT_DESKTOP", "XDG_GREETER_DATA_DIR", "LIBVIRT_DEFAULT_URI",
		"GPG_AGENT_INFO", "DESKTOP_SESSION","QT_IM_MODULE", "XDG_MENU_PREFIX",
		"XDG_SESSION_PATH", "USER", "DBUS_SESSION_BUS_ADDRESS", "DOCKER_HOST",
		"SSH_AGENT_LAUNCHER", "GTK_MODULES", "XDG_CONFIG_DIRS",
		"GTK_IM_MODULE", "XDG_SESSION_DESKTOP", "QT_ACCESSIBILITY",
		"GNOME_DESKTOP_SESSION_ID", "KRB5CCNAME", "LOGNAME",
		"GNOME_TERMINAL_SERVICE", "VTE_VERSION", "PATH", "XDG_RUNTIME_DIR",
		"XDG_DATA_DIRS", "XDG_SEAT_PATH", "SHELL", "XMODIFIERS",
		"XDG_SESSION_TYPE", "HOME", "COLORTERM", "XAUTHORITY", "PWD",
		"XDG_SESSION_CLASS", "TERM", "GDMSESSION", "DISPLAY", "SHLVL",
		"OLDPWD", "_", NULL};

	return (env);
}

char	**get_environment(void)
{
	int		i;
	char	*path;
	char	*env;
	char	**new_env;
	char	**list_env;

	i = 0;
	list_env = list_environment();
	while (list_env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (list_env[i])
	{
		path = getenv(list_env[i]);
		if (path)
			env = ft_strjoin_free(ft_strjoin(list_env[i], "="), path);
		else
			env = ft_strdup(list_env[i]);
		new_env[i] = env;
		i++;
	}
	return (new_env);
}

void	env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strchr(data->envp[i], '='))
		{
			ft_printf("%s\n", data->envp[i]);
		}
		i++;
	}
}
