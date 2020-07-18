/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:22:14 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/04 17:28:13 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memfill(void *s, void *elem, size_t number_of_elem,
	size_t sizeof_elem)
{
	size_t	i;

	i = 0;
	while (i < number_of_elem)
	{
		ft_memcpy(s + i * sizeof_elem, elem, sizeof_elem);
		i++;
	}
	return (s);
}
