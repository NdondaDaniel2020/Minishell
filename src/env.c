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

char	**get_env_1(void)
{
	static char	*env[] = {"SYSTEMD_EXEC_PID=8766",
		"SSH_AUTH_SOCK=/run/user/101270/keyring/ssh",
		"SESSION_MANAGER=local/c1r2s2.42luanda.com:@/tmp/.ICE-unix/8745,unix/\
c1r2s2.42luanda.com:/tmp/.ICE-unix/8745",
		"GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/\
b28597e8_e7ea_4fc0_b2d9_3d4e1f8fafb3",
		"LANG=en_US.UTF-8", "XDG_CURRENT_DESKTOP=ubuntu:GNOME",
		"XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/nmatondo",
		"LIBVIRT_DEFAULT_URI=qemu:///system",
		"GPG_AGENT_INFO=/run/user/101270/gnupg/S.gpg-agent:0:1",
		"DESKTOP_SESSION=ubuntu",
		"QT_IM_MODULE=ibus", "XDG_MENU_PREFIX=gnome-",
		"XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session1",
		"USER=nmatondo",
		"DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/101270/bus",
		"DOCKER_HOST=unix:///run/user/101270/docker.sock",
		"SSH_AGENT_LAUNCHER=gnome-keyring", "GTK_MODULES=gail:atk-bridge",
		"XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg",
		"GTK_IM_MODULE=ibus", "XDG_SESSION_DESKTOP=ubuntu", NULL};

	return (env);
}

char	**get_env_2(void)
{
	static char	*env[] = {"QT_ACCESSIBILITY=1",
		"GNOME_DESKTOP_SESSION_ID=this-is-deprecated",
		"KRB5CCNAME=FILE:/tmp/krb5cc_101270_uwgfLh",
		"LOGNAME=nmatondo",
		"GNOME_TERMINAL_SERVICE=:1.80", "VTE_VERSION=6800",
		"PATH=/nfs/homes/nmatondo/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:\
/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
		"XDG_RUNTIME_DIR=/run/user/101270",
		"XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/nfs/homes/nmatondo/\
.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/\
share:/usr/share:/var/lib/snapd/desktop",
		"XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0",
		"SHELL=/bin/zsh",
		"XMODIFIERS=@im=ibus", "XDG_SESSION_TYPE=x11",
		"HOME=/nfs/homes/nmatondo", "COLORTERM=truecolor",
		"XAUTHORITY=/nfs/homes/nmatondo/.Xauthority",
		"PWD=",
		"XDG_SESSION_CLASS=user", "TERM=xterm-256color",
		"GDMSESSION=ubuntu", "DISPLAY=:0", "SHLVL=1",
		"OLDPWD=", "_=/usr/bin/env", NULL};

	return (env);
}

char	**concat_env(char **env1, char **env2)
{
	int		i;
	int		len1;
	int		len2;
	char	**result;

	i = 0;
	len1 = 0;
	len2 = 0;
	while (env1[len1])
		len1++;
	while (env2[len2])
		len2++;
	result = ft_calloc((len1 + len2 + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (i < (len1 + len2))
	{
		if (i < len1)
			result[i] = ft_strdup(env1[i]);
		else
			result[i] = ft_strdup(env2[i - len1]);
		i++;
	}
	return (result);
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
