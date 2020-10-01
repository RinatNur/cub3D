/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 12:21:15 by jheat             #+#    #+#             */
/*   Updated: 2020/05/26 23:49:15 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *s, int c, size_t n)
{
	int		i;

	i = 0;
	while (n--)
	{
		*((unsigned char *)s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}
