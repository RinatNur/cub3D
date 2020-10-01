/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 00:03:56 by jheat             #+#    #+#             */
/*   Updated: 2020/05/24 00:04:44 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		src_len;
	size_t		dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len > size)
		dst_len = size;
	if (dst_len == size)
		return (size + src_len);
	if (src_len < (size - dst_len))
		ft_memcpy((dst + dst_len), src, (src_len + 1));
	else
	{
		ft_memcpy((dst + dst_len), src, (size - dst_len - 1));
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}
