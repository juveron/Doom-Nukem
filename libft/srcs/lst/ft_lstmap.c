/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 22:31:01 by kguibout          #+#    #+#             */
/*   Updated: 2018/12/18 10:50:52 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_lst(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cur;
	t_list	*tmp;
	t_list	*newelem;
	t_list	*map;

	cur = lst;
	map = NULL;
	while (cur != NULL && f != NULL)
	{
		tmp = f(cur);
		if ((newelem = ft_lstnew(tmp->content, tmp->content_size)) == NULL)
		{
			ft_lstdel(&map, &free_lst);
		}
		ft_lstaddend(&map, newelem);
		cur = cur->next;
	}
	return (map);
}
