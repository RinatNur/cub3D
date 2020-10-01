/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 00:22:17 by jheat             #+#    #+#             */
/*   Updated: 2020/05/24 00:23:32 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		little_len;
	size_t		j;
	size_t		i;

	i = 0;
	little_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	if (ft_strlen(big) < little_len || len < little_len)
		return (NULL);
	while (big[i] && i <= len - little_len)
	{
		j = 0;
		while (little[j] && little[j] == big[i + j])
			j++;
		if (j == little_len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
