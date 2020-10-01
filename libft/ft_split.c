/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:25:47 by jheat             #+#    #+#             */
/*   Updated: 2020/05/26 11:56:08 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			num_of_words(char const *s, char c)
{
	int		n;

	n = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
				s++;
			s--;
			n++;
		}
		s++;
	}
	return (n);
}

static int			get_len_str(char const *s, char c, int i)
{
	int		n;

	n = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		n++;
		i++;
	}
	return (n);
}

static void			add_str(char *str, char const *s, char c, int *i)
{
	int		n;

	n = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	while (s[*i] && s[*i] != c)
	{
		str[n] = s[*i];
		(*i)++;
		n++;
	}
	(*i)--;
	str[n] = '\0';
}

static char			**split_fill(char **arr, char const *s, char c)
{
	int		n;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		n = get_len_str(s, c, i);
		if (n == 0)
			break ;
		if (!(arr[j] = (char *)malloc(sizeof(char) * (n + 1))))
		{
			while (j)
				free(arr[j--]);
			free(arr);
			return (NULL);
		}
		add_str(arr[j], s, c, &i);
		i++;
		j++;
	}
	return (arr);
}

char				**ft_split(char const *s, char c)
{
	char	**arr;
	int		num_of_str;

	if (!s)
		return (NULL);
	num_of_str = num_of_words(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (num_of_str + 1))))
		return (NULL);
	arr[num_of_str] = NULL;
	if (!num_of_str)
		return (arr);
	arr = split_fill(arr, s, c);
	return (arr);
}
