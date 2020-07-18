/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 14:54:12 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 17:18:38 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"
#include "render.h"
#include "pvs_internal.h"

static bool	check_and_add_sector(t_vector *sector, t_unique_id id)
{
	size_t		i;
	t_unique_id	*ids;

	i = 0;
	ids = sector->items;
	while (i < sector->total)
	{
		if (ids[i] == id)
			return (true);
		++i;
	}
	return (vector_push(sector, &id));
}

/*
**	Compute portal if is totally in the view frustum
*/

bool		compute_pvs_internal(t_pvs_handle_2 *pvs)
{
	size_t	i;
	t_wall	*walls;
	int		ret;

	i = (size_t)-1;
	walls = pvs->sector->walls.items;
	if (!check_and_add_sector(pvs->vector, pvs->sector->id))
		return (false);
	if (pvs->s.iter > 40)
		return (true);
	while (++i < pvs->sector->walls.total)
	{
		if (walls[i].v1 == pvs->wall->v2 || walls[i].v2 == pvs->wall->v1)
			continue ;
		else if (walls[i].neighbor)
		{
			pvs->wall_i = &walls[i];
			ret = compute_pvs_internal_p2(pvs);
			if (ret == -1)
				return (false);
		}
	}
	return (true);
}

bool		compute_pvs(t_sector *sector, t_vector *vector)
{
	t_wall			*walls;
	t_pvs_handle_2	pvs;
	size_t			i;

	vector_init(vector, sizeof(t_unique_id));
	walls = sector->walls.items;
	i = 0;
	pvs.vector = vector;
	while (i < sector->walls.total)
	{
		if (walls[i].neighbor)
		{
			pvs.wall = &walls[i];
			pvs.sector = walls[i].neighbor;
			pvs.s = (t_pvs_handle){.start1 = walls[i].v1->v.v,
					.start2 = walls[i].v2->v.v, .available = false,
					.sector = sector};
			if (!compute_pvs_internal(&pvs))
				return (false);
		}
		++i;
	}
	return (true);
}
