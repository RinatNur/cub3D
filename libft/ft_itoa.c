/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 18:07:33 by jheat             #+#    #+#             */
/*   Updated: 2020/05/27 16:54:09 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_numlen(int num, int sign)
{
	int		len;

	len = 1;
	while ((num /= 10))
		len++;
	return (len + sign);
}

static int			num_negativ(int n, int *f)
{
	if (n == -2147483648)
	{
		*f = 1;
		n += 1;
	}
	return (n *= (-1));
}

char				*ft_itoa(int n)
{
	char		*str;
	int			f;
	int			i;
	int			sign;
	int			len;

	f = 0;
	sign = (n < 0) ? 1 : 0;
	len = ft_numlen(n, sign);
	i = len;
	if (sign)
		n = num_negativ(n, &f);
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (i-- > sign)
	{
		str[i] = (n % 10 + '0');
		n = n / 10;
	}
	if (f == 1)
		str[len - 1] += 1;
	if (sign)
		str[i] = '-';
	return (str);
}
