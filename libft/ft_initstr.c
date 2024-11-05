/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:04:14 by nmatondo          #+#    #+#             */
/*   Updated: 2024/07/18 13:08:13 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_initstr(char **str)
{
	char	*ini_str;

	ini_str = *str;
	ini_str = (char *)malloc(sizeof(char) * 1);
	if (!ini_str)
		return (0);
	ini_str[0] = '\0';
	return (1);
}
