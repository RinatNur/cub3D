/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:10:35 by jheat             #+#    #+#             */
/*   Updated: 2020/09/14 14:57:01 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*check_new_line(char **line, char **buf_tail)
{
	char		flag;
	char		*p;
	char		*p_l;

	p = NULL;
	flag = 1;
	if ((p = ft_strchr_gnl(*buf_tail, '\n')))
	{
		*p = '\0';
		if (!(p_l = ft_strdup_gnl(++p, 0)))
			return (p = &flag);
		if (!(*line = ft_strdup_gnl(*buf_tail, 1)))
		{
			free(p_l);
			return (p = &flag);
		}
		if (!(*buf_tail = ft_strdup_gnl(p_l, 1)))
		{
			free(*line);
			return (p = &flag);
		}
	}
	return (p);
}

static char		*check_buf_tail(char **line, char **buf_tail)
{
	char		flag;
	char		*p;

	p = NULL;
	flag = 1;
	if (*buf_tail)
	{
		if ((p = check_new_line(line, &(*buf_tail))) && *p == 1)
			return (p);
		else if (NULL == p)
		{
			if (!(*line = ft_strdup_gnl(*buf_tail, 1)))
				return (p = &flag);
			*buf_tail = NULL;
		}
	}
	else
	{
		if (!(*line = ft_strdup_gnl("", 0)))
			return (p = &flag);
	}
	return (p);
}

int				get_next_line(int fd, char **line)
{
	static char		*buf_tail;
	char			buf[2];
	int				num_of_reading_bytes;
	char			*p;

	if (fd < 0 || !line || (read(fd, 0, 0) == -1) ||
	((p = check_buf_tail(line, &buf_tail)) && *p == 1))
		return (-1);
	while (!p && (num_of_reading_bytes = read(fd, buf, 1)) > 0)
	{
		buf[1] = '\0';
		if ((p = ft_strchr_gnl(buf, '\n')))
		{
			*p = '\0';
			if (!(buf_tail = ft_strdup_gnl(++p, 0)))
			{
				free(*line);
				return (-1);
			}
		}
		if (!(*line = ft_strjoin_gnl(*line, buf)))
			return (-1);
	}
	return (num_of_reading_bytes || ft_strlen_gnl(buf_tail) || p ? 1 : 0);
}
