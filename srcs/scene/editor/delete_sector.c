/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:44:15 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 16:34:02 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static t_u64	delete_sector_p2(t_sector *sector, t_env *env,
	t_u64 num_deleted)
{
	if (!triangulate_all_neighbor(sector)
		|| !map_delete(env->current_map->sectors, sector->id))
		return ((t_u64)-1);
	free_sector(sector);
	return (num_deleted);
}

t_u64			delete_sector(t_sector *sector, t_env *env)
{
	size_t	i;
	t_wall	*walls;
	t_u64	num_deleted;

	num_deleted = 0;
	walls = sector->walls.items;
	i = 0;
	while (i < sector->walls.total)
	{
		if (walls[i].neighbor)
			remove_neighbor(walls[i].neighbor, sector);
		if (!point_remove_sector(walls[i].v1, sector))
			return ((t_u64)-1);
		if (walls[i].v1->sector->total == 0)
		{
			if (!map_delete(env->current_map->vertices, walls[i].v1->id))
				return ((t_u64)-1);
			num_deleted++;
			point_free(walls[i].v1);
		}
		i++;
	}
	return (delete_sector_p2(sector, env, num_deleted));
}
