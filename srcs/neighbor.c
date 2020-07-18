/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 19:17:01 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/28 08:50:05 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	remove_neighbor(t_sector *sector, t_sector *neighbor)
{
	size_t	i;
	t_wall	*walls;

	walls = sector->walls.items;
	i = 0;
	while (i < sector->walls.total)
	{
		if (walls[i].neighbor == neighbor)
			walls[i].neighbor = NULL;
		i++;
	}
}
