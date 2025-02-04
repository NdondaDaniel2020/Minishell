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

int main()
{
	int		i;
	char	*str;
	char	**result;

	i = 0;
	str = ft_strdup("echo \"hello world\" 'hello world' hello world");
	result = split(str, ' ');
	while (result[i])
	{
		printf("[%s]\n", result[i]);
		i++;
	}
	free(str);
	free_matrix(result);
	return (0);
}
