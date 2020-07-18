/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:42:55 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/13 17:29:03 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	remap_neighbor(t_sector *sector, t_env *env)
{
	size_t	i;
	t_wall	*wall;

	wall = sector->walls.items;
	i = 0;
	while (i < sector->walls.total)
	{
		if (wall[i].neighbor == (t_sector *)-1)
			wall[i].neighbor = NULL;
		else
		{
			wall[i].neighbor = *(t_sector **)map_get(env->current_map->sectors,
				(t_u64)wall[i].neighbor);
		}
		i++;
	}
}

void	free_sector_event(t_sector *sector, t_vector *vertices)
{
	size_t	i;
	t_point	**point;

	if (!sector || !vertices)
		return ;
	free_sector(sector);
	if (vertices)
	{
		i = 0;
		point = vertices->items;
		while (i < vertices->total)
		{
			point_free(point[i]);
			++i;
		}
	}
	vector_free(vertices);
}

void	free_sector(t_sector *sector)
{
	mtl_destroy(&sector->mtl_ceil);
	mtl_destroy(&sector->mtl_floor);
	vector_free(&sector->triangle_bottom);
	if (sector->has_roof)
		vector_free(&sector->triangle_top);
	vector_free(&sector->pvs.sector);
	free_walls_sector(&sector->walls);
	free(sector);
}
