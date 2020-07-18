/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strssplit_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:59:13 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/02 15:05:46 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_error(char ***tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		ft_strdel(&(*tab)[i++]);
	ft_strdel((*tab));
	return (0);
}
