/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 08:51:56 by jheat             #+#    #+#             */
/*   Updated: 2020/05/25 11:24:54 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_char(char const *set, char c)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		finish;
	int		start;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	finish = ft_strlen(s1) - 1;
	while (s1[start] && check_char(set, s1[start]))
		start++;
	if (!s1[start])
		return (!(str = ft_calloc(1, 1)) ? NULL : str);
	while (s1[finish] && check_char(set, s1[finish]))
		finish--;
	if (!(str = (char *)malloc(sizeof(char) * (finish - start + 2))))
		return (NULL);
	while (start <= finish)
	{
		str[i++] = s1[start++];
	}
	str[i] = '\0';
	return (str);
}
