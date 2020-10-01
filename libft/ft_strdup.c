/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:35:14 by jheat             #+#    #+#             */
/*   Updated: 2020/05/23 12:11:01 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*buff;
	int		i;

	i = 0;
	while (str[i])
		i++;
	buff = (char *)malloc(sizeof(*str) * (i + 1));
	if (buff == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		buff[i] = str[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
