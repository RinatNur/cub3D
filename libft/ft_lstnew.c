/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 19:14:09 by jheat             #+#    #+#             */
/*   Updated: 2020/06/02 19:29:13 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*new_el;

	if ((new_el = malloc(sizeof(t_list))))
	{
		new_el->content = content;
		new_el->next = NULL;
		return (new_el);
	}
	return (NULL);
}
