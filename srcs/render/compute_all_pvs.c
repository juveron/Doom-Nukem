/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_all_pvs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 03:11:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/12 13:19:27 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "render.h"

static bool	compute_map(t_doom_map *map)
{
	t_sector	*sector;
	size_t		i;

	i = 0;
	while (i < map->sectors->total)
	{
		sector = *(t_sector **)map_get_index(map->sectors, i);
		vector_free(&sector->pvs.sector);
		if (!compute_pvs(sector, &sector->pvs.sector))
			return (false);
		++i;
	}
	return (true);
}

bool		compute_all_pvs(t_env *env)
{
	t_doom_map	**maps;
	size_t		i;

	i = 0;
	maps = env->maps.items;
	while (i < env->maps.total)
	{
		if (!compute_map(maps[i]))
			return (false);
		++i;
	}
	return (true);
}
