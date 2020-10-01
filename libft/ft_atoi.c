/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 00:28:49 by jheat             #+#    #+#             */
/*   Updated: 2020/05/24 00:47:32 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i])
	{
		while ((str[i] == 32) || (str[i] > 8 && str[i] < 14))
			i++;
		if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		while (ft_isdigit(str[i]))
		{
			res = res * 10 + str[i] - '0';
			i++;
		}
		return (res == 0 ? 0 : (res * sign));
	}
	return (0);
}
