/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 12:18:10 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/02 12:20:34 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist_handler	*ft_dlist_create(void)
{
	t_dlist_handler *dlist_handler;

	return (dlist_handler = ft_memalloc(sizeof(t_dlist_handler)));
}
