/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:58:47 by jheat             #+#    #+#             */
/*   Updated: 2020/10/18 18:00:44 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			ft_free_mas(char **mas)
{
	int		i;

	i = -1;
	while (mas[++i])
		free(mas[i]);
	free(mas);
}

void			free_is_valid(const char *s, char *line)
{
	if (*s == 'R' || (*s == 'N' && *(s + 1) == 'O')
		|| (*s == 'S' && *(s + 1) == 'O')
		|| (*s == 'W' && *(s + 1) == 'E') || (*s == 'E' && *(s + 1) == 'A')
		|| *s == 'S' || *s == 'F' || *s == 'C')
		free(line);
}

char			*skip_space(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}
