
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


int main(void)
{
    t_new_list *list = NULL;
    t_new_list *new_node;
	char *contentx[] = {"ItemXItem", NULL};
    char *content1[] = {"Item 1", NULL};
    char *content2[] = {"Item 2", NULL};
    char *content3[] = {"Item 3", NULL};

    new_node = ft_lstnew_new(content1);
    ft_lstnew_addback(&list, new_node);

    new_node = ft_lstnew_new(content2);
    ft_lstnew_addback(&list, new_node);

    new_node = ft_lstnew_new(content3);
    ft_lstnew_addfront(&list, new_node);

	//////////////////////////////////////////
	new_node = ft_lstnew_new(contentx);
    ft_lstnew_add_after_position(&list, list->next->next, new_node);
	//////////////////////////////////////////

    // Print the list to verify
    t_new_list *current = list;
    while (current)
    {
        printf("Content: %s\n", current->content[0]);
        current = current->next;
    }

    // Free the list
    current = list;
    t_new_list *next;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    return 0;
}
