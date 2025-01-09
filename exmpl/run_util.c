
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
