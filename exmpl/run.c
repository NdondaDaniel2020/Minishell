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

char	*ft_charjoin_free(char *s1, char c)
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
	free(s1);
	return (join);
}

char	*substring(const char *str, int start, int end)
{
	int 	len;
	char	*sub;

	len = strlen(str);
	if (start > end)
		return (NULL);
	if (start < 0)
		start = 0;
	if (end > len)
		end = len;
	sub = (char *)malloc((end - start + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, str + start, end - start + 1);
	sub[end - start] = '\0';
	return (sub);
}

/////////// 

////////////

/////////// 

///////////

int	main(void)
{
	int		i; // ->nao usas
	t_data	data;
	char	**matrix;

	i = 0;  // ->nao usas removidos
	matrix = NULL;
	init_data(&data);
	data.envp = get_all_environment();
	matrix = split_2("echo:\" ' \"   $HOME   \" ' \" '   $HOME   ' \" \" ' \"  $HOME  \" ' \" '  $HOME  ' \" \"   $HOME   \" '   $HOME   '", ':');
	// 
	environment_variation_expansion(&matrix, &data);
	printf("\n\n\n");
	while (matrix[i])
	{
		printf("(%s)\n", matrix[i]);
		i++;
	}
	free_matrix(matrix);
	free_data(&data);
	return (0);
}
