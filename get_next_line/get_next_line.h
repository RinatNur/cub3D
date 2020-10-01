/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:33:35 by jheat             #+#    #+#             */
/*   Updated: 2020/09/14 14:57:01 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

char		*ft_strdup_gnl(char *str, int flag);
int			get_next_line(int fd, char **line);
char		*ft_strjoin_gnl(char *s1, char const *s2);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strchr_gnl(const char *s, int c);
int			ft_free(char *s, int flag);

#endif
