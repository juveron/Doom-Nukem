/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickup_object_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:53:28 by thboura           #+#    #+#             */
/*   Updated: 2020/07/06 11:41:03 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	verify_objects_in_sector(t_env *env, t_sector *sector,
	bool check_inside)
{
	size_t			i;
	t_pickup_object	**pickup_objects;

	pickup_objects = env->current_map->pickup_objects.items;
	i = 0;
	while (i < env->current_map->pickup_objects.total)
	{
		if (pickup_objects[i]->sector_id == sector->id)
		{
			if (check_inside)
			{
				if (!inside(&(t_vec2f){pickup_objects[i]->pos.x,
					pickup_objects[i]->pos.z}, sector, false))
					return (false);
			}
			return (true);
		}
		i++;
	}
	return (check_inside);
}

bool	object_out_of_sector(t_env *env, t_point *point)
{
	t_sector	*tmp_sector;
	size_t		i;

	i = 0;
	while (i < point->sector->total)
	{
		tmp_sector = *(t_sector **)map_get_index(point->sector, i);
		if (!verify_objects_in_sector(env, tmp_sector, true))
			return (false);
		i++;
	}
	return (true);
}
