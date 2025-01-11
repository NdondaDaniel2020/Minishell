
#include "run.h"

void	ft_lstnew_addback(t_new_list **lst, t_new_list *new)
{
	t_new_list	*aux;

	if (lst)
	{
		if (new)
		{
			if (*lst == NULL)
				*lst = new;
			else
			{
				aux = *lst;
				while (aux->next)
					aux = aux->next;
				aux->next = new;
			}
		}
	}
}

void	ft_lstnew_addfront(t_new_list **lst, t_new_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

void	ft_lstnew_addafter_pos(
	t_new_list **lst, t_new_list *ref, t_new_list *new)
{
	t_new_list	*aux;

	if (new)
	{
		if (*lst == NULL)
			ft_lstnew_addfront(lst, new);
		else
		{
			aux = *lst;
			while (aux && aux != ref)
				aux = aux->next;
			new->next = aux->next;
			aux->next = new;
		}
	}
}

t_new_list	*ft_lstnew_new(char **content)
{
	t_new_list	*new;

	new = (t_new_list *)malloc(sizeof(t_new_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_lstnew_size(t_new_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


void	ft_lstnew_free(char **matrix, t_new_list *removed)
{
	if (matrix)
		free_matrix(matrix);
	if (removed)
	{
		free(removed);
		removed = NULL;
	}
}

void	ft_lstnew_delfront(t_new_list **list)
{
	t_new_list	*removed;

	if (!list || !*list)
		return ;
	removed = *list;
	*list = removed->next;
	free_matrix(removed->content);
	free(removed);
	removed = NULL;
}

void	ft_lstnew_delback(t_new_list **list)
{
	t_new_list	*aux;
	t_new_list	*removed;

	if (!list || !*list)
		return ;
	if (!(*list)->next)
	{
		ft_lstnew_free((*list)->content, *list);
		*list = NULL;
		return ;
	}
	aux = *list;
	while (aux->next->next)
		aux = aux->next;
	if (aux->next)
	{
		removed = aux->next;
		aux->next = removed->next;
		ft_lstnew_free(removed->content, removed);
	}
}

/* remover mais tarde */
void	ft_show_lstnew(t_new_list *list)
{
	int	i;

	while (list)
	{
		if (!list->content)
		{
			list = list->next;
			continue ;
		}
		i = 0;
		while (list->content[i])
		{
			printf("[%d]: %s ", i, list->content[i]);
			i++;
		}
		printf("\n");
		list = list->next;
	}
}

void	init_data(t_data *data)
{
	data->path = NULL;
	data->list = NULL;
	data->space = false;
	data->output = NULL;
	data->command = NULL;
	data->put_amb = NULL;
	data->is_pipe = false;
	data->automatic_input = false;
	data->cpy_fd = -1;
	data->read_in_the_pipe = -1;
	data->write_on_the_pipe = -1;
	data->redirection_matrix = NULL;
}


static int	count_substrings(char *str, char chr)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			in_quotes = !in_quotes;
		}
		else if (*str == chr && !in_quotes)
		{
			count++;
			while (*str == chr)
				str++;
			continue ;
		}
		str++;
	}
	return (count + 1);
}

static void	init_split(t_split *split, char *str, char chr)
{
	split->len = 0;
	split->in_quotes = 0;
	split->substr_count = count_substrings(str, chr);
	split->result = malloc((split->substr_count + 1) * sizeof(char *));
	split->start = str;
	split->end = str;
}

static void	split_substring(int *i, t_split *split, char chr)
{
	split->len = split->end - split->start;
	split->result[*i] = malloc((split->len + 1) * sizeof(char));
	strncpy(split->result[*i], split->start, split->len);
	split->result[*i][split->len] = '\0';
	(*i)++;
	while (*split->end == chr)
		split->end++;
	split->start = split->end;
}

char	**split_2(char *str, char chr)
{
	int			i;
	t_split		split;

	i = 0;
	init_split(&split, str, chr);
	while (*split.end)
	{
		if (*split.end == '"' || *split.end == '\'')
			split.in_quotes = !split.in_quotes;
		else if (*split.end == chr && !split.in_quotes)
		{
			split_substring(&i, &split, chr);
			continue ;
		}
		split.end++;
	}
	split.result[i] = strdup(split.start);
	split.result[split.substr_count] = NULL;
	return (split.result);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

////////////////////


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

char	**get_all_environment(void)
{
	int		i;
	char	*env;
	char	*path;
	char	**new_env;
	char	**list_env;

	list_env = list_environment();
	i = len_matrix(list_env);
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (list_env[i])
	{
		path = getenv(list_env[i]);
		if (path)
		{
			env = ft_strjoin_free(ft_strjoin(list_env[i], "="), path);
			if (!ft_strncmp(env, "SHLVL", ft_strlen(env) - 2))
				env = increment_shlv(env);
		}
		else
			env = ft_strdup(list_env[i]);
		new_env[i] = env;
		i++;
	}
	return (new_env);
}

char	*get_env(char *env, t_data *data)
{
	int	i;
	int	ix;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], env, ft_strlen(env))
			&& (data->envp[i][ft_strlen(env)] == '='
			|| data->envp[i][ft_strlen(env)] == '\0'))
		{
			ix = 0;
			while (data->envp[i][ix] != '=')
				ix++;
			return (data->envp[i] + ix + 1);
		}
		i++;
	}
	return (NULL);
}

void	free_data(t_data *data)
{
	if (data->path)
		free_matrix(data->path);
	if (data->envp)
		free_matrix(data->envp);
}

int	len_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

//////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
char	*ft_charjoin(char *s1, char c)
{
	char	*join;
	int		l1;
	int		i;

	if (!s1 && !c)
		return (NULL);
	i = 0;
	l1 = ft_strlen(s1);
	join = malloc((l1 + 2) * sizeof(char));
	if (!join)
		return (NULL);
	while (i < (l1 + 1))
	{
		if (i < l1)
			join[i] = s1[i];
		else
			join[i] = c;
		i++;
	}
	join[i] = '\0';
	return (join);
}

static char	*read_all_path(int i, t_new_list *aux, t_data *data, DIR *open_dir)
{
	char			*dir_path;
	struct dirent	*entry;

	entry = readdir(open_dir);
	while (entry != NULL)
	{
		if (!ft_strncmp(entry->d_name, aux->content[0], ft_strlen(entry->d_name))
			&& ft_strlen(entry->d_name) == ft_strlen(data->list->content[0]))
		{
			dir_path = ft_charjoin(data->path[i], '/');
			dir_path = ft_strjoin_free(dir_path, entry->d_name);
			closedir(open_dir);
			return (dir_path);
		}
		entry = readdir(open_dir);
	}
	return (NULL);
}

char	*get_valid_path(t_new_list *aux, t_data *data)
{
	int				i;
	char			*dir_path;
	DIR				*open_dir;

	i = 0;
	if (data->path == NULL)
		return (NULL);
	while (data->path[i])
	{
		open_dir = opendir(data->path[i]);
		if (open_dir)
		{
			dir_path = read_all_path(i, aux, data, open_dir);
			if (dir_path)
				return (dir_path);
		}
		closedir(open_dir);
		i++;
	}
	return (NULL);
}

////////////////////////////////////////////////////////////////////////////////////

bool	all_char_equal_char(char *str, char chr)
{
	if (ft_strlen(str) == 0)
		return (false);
	while (*str)
	{
		if (*str != chr)
			return (false);
		str++;
	}
	return (true);
}

bool	valid_string_condition_for_redirection(char *str)
{
	return ((ft_strncmp(str, ">", 1) == 0 && ft_strlen(str) == 1)
		|| (ft_strncmp(str, "<", 1) == 0 && ft_strlen(str) == 1)
		|| (ft_strncmp(str, "<<", 2) == 0 && ft_strlen(str) == 2)
		|| (ft_strncmp(str, ">>", 2) == 0 && ft_strlen(str) == 2)
		|| (ft_strncmp(str, "<>", 2) == 0 && ft_strlen(str) == 2));
}

bool	condition_add_more_one(int i, char ***matrix)
{
	return ((*matrix)[i] != NULL
		&& (all_char_equal_char((*matrix)[i], '"')
			|| all_char_equal_char((*matrix)[i], '\'')));
}

static void	special_adjust(char ***start)
{
	int		s;
	int		len_m;
	char	*aux;

	if (start == NULL || *start == NULL)
		return ;
	s = 0;
	len_m = len_matrix((*start));
	if (len_m <= 1)
		return ;
	aux = (*start)[0];
	while (s < len_m - 1)
	{
		(*start)[s] = (*start)[s + 1];
		s++;
	}
	(*start)[s] = aux;
}

static void	last_adjust(int len, char **end, char **start, char ***matrix)
{
	int	i;
	int	e;
	int	s;

	i = 0;
	e = 0;
	s = 0;
	if (start == NULL || *start == NULL || matrix == NULL || *matrix == NULL)
		return ;
	if (ft_strlen(start[0]) == 0)
		special_adjust(&start);
	while (i < len)
	{
		if (i < len_matrix(start))
			(*matrix)[i++] = start[s++];
		else
			(*matrix)[i++] = end[e++];
	}
	free(end);
	free(start);
}

void	ajust_all_position(char ***matrix)
{
	int		i;
	int		e;
	int		s;
	char	**end;
	char	**start;

	i = 0;
	e = 0;
	s = 0;
	end = (char **)ft_calloc(len_matrix((*matrix)) + 1, sizeof(char *));
	start = (char **)ft_calloc(len_matrix((*matrix)) + 1, sizeof(char *));
	while (i < len_matrix((*matrix)))
	{
		if (valid_string_condition_for_redirection((*matrix)[i]))
		{
			end[e++] = (*matrix)[i++];
			if ((*matrix)[i] != NULL)
				end[e++] = (*matrix)[i++];
			if (condition_add_more_one(i, matrix))
				end[e++] = (*matrix)[i++];
		}
		else
			start[s++] = (*matrix)[i++];
	}
	last_adjust(len_matrix((*matrix)), end, start, matrix);
}

void	insert_data(t_data *data, char *command)
{
	int		i;
	int		len_m;
	char	**matrix;
	char	**spliting;

	i = 0;
	data->command = command;
	spliting = split_2(command, '|');
	len_m = len_matrix(spliting);
	if (len_m > 1)
		data->is_pipe = true;
	else
		data->is_pipe = false;
	while (spliting[i])
	{
		matrix = split_2(spliting[i], ' ');
		ajust_all_position(&matrix);
		ft_lstnew_addback(&data->list, ft_lstnew_new(matrix));
		free(spliting[i]);
		i++;
	}
	free(spliting);
}

////////////////////////////////////////////////////////////////////////////////////

void	free_all_data(t_data *data)
{
	if (!data)
		return ;
	if (data->list)
	{
		while (data->list)
			ft_lstnew_delback(&data->list);
		data->list = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

