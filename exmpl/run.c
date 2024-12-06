
#include <term.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <termios.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>

typedef struct s_new_list
{
	int					item;
	char				**content;
	struct s_new_list	*next;
}						t_new_list;

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

void    ft_lstnew_addback(t_new_list **lst, t_new_list *new)
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

void    ft_lstnew_addfront(t_new_list **lst, t_new_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

t_new_list  *ft_lstnew_new(char **content)
{
	t_new_list	*new;

	new = (t_new_list *)malloc(sizeof(t_new_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int     ft_lstnew_size(t_new_list *lst)
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
        return;
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
        return;
    if (!(*list)->next)
    {
        ft_lstnew_free((*list)->content, *list);
        *list = NULL;
        return;
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

void	ft_show_lstnew(t_new_list *list)
{
    int	i;

    while (list)
    {
        if (!list->content)
        {
            list = list->next;
            continue;
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

int main(void)
{
	int			i;
	t_new_list	*list;

	i = 0;
	list = NULL;
	ft_lstnew_addback(&list, ft_lstnew_new(ft_split("hello world", ' ')));
	ft_lstnew_addfront(&list, ft_lstnew_new(ft_split("cort de leon", ' ')));
	printf("size: %d\n", ft_lstnew_size(list));
	ft_show_lstnew(list);
	while (list)
		ft_lstnew_delfront(&list);


	ft_lstnew_addback(&list, ft_lstnew_new(ft_split("hello world Ndonda", ' ')));
	ft_lstnew_addfront(&list, ft_lstnew_new(ft_split("Ndonda Daniel Matondo", ' ')));
	ft_lstnew_addfront(&list, ft_lstnew_new(ft_split("cort de leon Matondo", ' ')));
	printf("size: %d\n", ft_lstnew_size(list));
	ft_show_lstnew(list);
	while (list)
		ft_lstnew_delback(&list);


	ft_lstnew_addback(&list, ft_lstnew_new(ft_split("hello world Ndonda", ' ')));
	ft_lstnew_addfront(&list, ft_lstnew_new(ft_split("Ndonda Daniel Matondo", ' ')));
	ft_lstnew_addfront(&list, ft_lstnew_new(ft_split("cort de leon Matondo", ' ')));
		ft_lstnew_addfront(&list, ft_lstnew_new(ft_split("Elgreande Ndonda", ' ')));
	ft_lstnew_addfront(&list, ft_lstnew_new(ft_split("Matondo Matondo", ' ')));
	printf("size: %d\n", ft_lstnew_size(list));
	ft_show_lstnew(list);
	while (list)
		ft_lstnew_delback(&list);
}
