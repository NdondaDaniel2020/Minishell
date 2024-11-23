
#include "../libft/libft.h"
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>


// static char	**list_environment(void)
// {
// 	static char	*env[] = {"SYSTEMD_EXEC_PID", "SSH_AUTH_SOCK",
// 		"SESSION_MANAGER", "GNOME_TERMINAL_SCREEN", "LANG",
// 		"XDG_CURRENT_DESKTOP", "XDG_GREETER_DATA_DIR", "LIBVIRT_DEFAULT_URI",
// 		"GPG_AGENT_INFO", "DESKTOP_SESSION","QT_IM_MODULE", "XDG_MENU_PREFIX",
// 		"XDG_SESSION_PATH", "USER", "DBUS_SESSION_BUS_ADDRESS", "DOCKER_HOST",
// 		"SSH_AGENT_LAUNCHER", "GTK_MODULES", "XDG_CONFIG_DIRS",
// 		"GTK_IM_MODULE", "XDG_SESSION_DESKTOP", "QT_ACCESSIBILITY",
// 		"GNOME_DESKTOP_SESSION_ID", "KRB5CCNAME", "LOGNAME",
// 		"GNOME_TERMINAL_SERVICE", "VTE_VERSION", "PATH", "XDG_RUNTIME_DIR",
// 		"XDG_DATA_DIRS", "XDG_SEAT_PATH", "SHELL", "XMODIFIERS",
// 		"XDG_SESSION_TYPE", "HOME", "COLORTERM", "XAUTHORITY", "PWD",
// 		"XDG_SESSION_CLASS", "TERM", "GDMSESSION", "DISPLAY", "SHLVL",
// 		"OLDPWD", "_", NULL};

// 	return (env);
// }
// 	// change_value_path()

// char	**get_environment(void)
// {
// 	int		i;
// 	char	*path;
// 	char	*env;
// 	char	**new_env;
// 	char	**list_env;

// 	i = 0;
// 	list_env = list_environment();
// 	while (list_env[i])
// 		i++;
// 	new_env = ft_calloc(i + 1, sizeof(char *));
// 	i = 0;
// 	while (list_env[i])
// 	{
// 		path = getenv(list_env[i]);
// 		/////////
// 		if (!ft_strncmp(path, "SHLVL=1", ft_strlen(path)))
// 		/////////
// 		if (path)
// 		{
// 			env = ft_strjoin_free(ft_strjoin(list_env[i], "="), path);
// 		}
// 		else
// 			env = ft_strdup(list_env[i]);
// 		new_env[i] = env;
// 		i++;
// 	}
// 	return (new_env);
// }

// int	main(void)
// {
// 	int		i = 0;
// 	char	**list;

// 	list = get_environment();
// 	while (list[i])
// 	{
// 		ft_printf("%s\n", list[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (list[i])
// 	{
// 		free(list[i]);
// 		i++;
// 	}
// 	free(list);
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *increment_shlvl(const char *shlvl_str)
{
	int 	i;
    int 	shlvl;
    int 	temp_shlvl;
	int 	shlvl_str_len;
    size_t	prefix_len;
	size_t	new_str_len;
    char	*new_shlvl_str;
	char	shlvl_str_value[12];

    prefix_len = 6;
    if (strncmp(shlvl_str, "SHLVL=", prefix_len) != 0)
        return (NULL);
    shlvl = atoi(shlvl_str + prefix_len);
    shlvl++;
    shlvl_str_len = 0;
    temp_shlvl = shlvl;
    while (temp_shlvl > 0)
	{
        shlvl_str_len++;
        temp_shlvl /= 10;
    }
    shlvl_str_value[shlvl_str_len] = '\0';
	i = shlvl_str_len - 1;
	while (i >= 0)
	{
		shlvl_str_value[i] = (shlvl % 10) + '0';
        shlvl /= 10;
		i--;
	}
    new_str_len = prefix_len + shlvl_str_len + 1;
    new_shlvl_str = (char *)malloc(new_str_len);
    if (new_shlvl_str == NULL)
        return (NULL);
    strcpy(new_shlvl_str, "SHLVL=");
    strcat(new_shlvl_str, shlvl_str_value);
    return (new_shlvl_str);
}

int main() {
    const char *shlvl_str = "SHLVL=9";
    char *new_shlvl_str = increment_shlvl(shlvl_str);

    if (new_shlvl_str) {
        printf("Original: %s\n", shlvl_str);
        printf("Incremented: %s\n", new_shlvl_str);
        free(new_shlvl_str); // Libera a memória alocada
    } else {
        printf("Invalid SHLVL string\n");
    }

    return 0;
}