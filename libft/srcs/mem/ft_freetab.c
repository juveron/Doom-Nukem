/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 08:26:17 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/02 14:00:08 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(void ***tab)
{
	void	**tmp;

	tmp = *tab;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	ft_memdel((void **)&(*tab));
}
