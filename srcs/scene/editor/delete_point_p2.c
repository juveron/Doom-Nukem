/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_point_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:00:55 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 16:01:33 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	free_tmp_handler(t_point *point, t_env *env, t_vector *tmp_handler,
	int ret)
{
	vector_free(tmp_handler);
	if (ret == 1)
	{
		map_delete(env->current_map->vertices, point->id);
		point_free(point);
	}
	return (ret);
}

int	remove_point(t_sector *sector, t_vector *tmp_handler, size_t i)
{
	t_u64		wall_index;
	t_deletion	del;
	t_wall		*walls;

	walls = sector->walls.items;
	wall_index = get_correct_index(sector->walls.total, i - 1);
	del.wall1 = wall_clone(&walls[wall_index]);
	del.wall2 = wall_clone(&walls[i]);
	walls[wall_index].v2 = walls[get_correct_index(sector->walls.
			total, i + 1)].v1;
	del.sector_id = sector->id;
	del.wall_index = wall_index;
	if (!vector_push(tmp_handler, &del))
		return (-1);
	if (walls[wall_index].neighbor != walls[i].neighbor)
		walls[wall_index].neighbor = NULL;
	free_wall(&walls[i]);
	if (!vector_delete(&sector->walls, i))
		return (-1);
	return (1);
}

int	check_level(t_point *point, t_vector *tmp_handler, t_env *env)
{
	t_deletion	*deletion;
	size_t		i;

	if (!verify_sector_level_points(env, point)
		|| !object_out_of_sector(env, point))
	{
		cancel_point_deletion(env, (t_deletion *)tmp_handler->items,
			tmp_handler->total);
		deletion = tmp_handler->items;
		i = 0;
		while (i < tmp_handler->total)
		{
			free_wall_event(deletion[i].wall1);
			free_wall_event(deletion[i].wall2);
			++i;
		}
		return (free_tmp_handler(point, env, tmp_handler, 0));
	}
	return (1);
}
