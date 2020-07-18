/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:43:30 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 16:00:43 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delete_point_internal.h"

static int	remove_point_from_sector(t_point *point, t_sector *sector,
	t_vector *tmp_handler, t_env *env)
{
	size_t		i;
	t_wall		*walls;

	i = 0;
	walls = sector->walls.items;
	while (i < sector->walls.total)
	{
		if (point->id == walls[i].v1->id)
		{
			if (sector->walls.total == 3)
			{
				ft_printf("Sector %zu is a triangle.\n", i);
				return (free_tmp_handler(point, env, tmp_handler, 0));
			}
			if (remove_point(sector, tmp_handler, i) != 1)
				return (free_tmp_handler(point, env, tmp_handler, -1));
			if (!triangulate_sector(sector))
				return (free_tmp_handler(point, env, tmp_handler, -1));
			return (check_level(point, tmp_handler, env));
		}
		++i;
	}
	return (0);
}

static bool	verify_sector_triangle(t_point *point, t_env *env)
{
	size_t		i;
	size_t		j;
	t_sector	*sector;
	t_wall		*walls;

	i = (size_t)-1;
	while (++i < env->current_map->sectors->total)
	{
		sector = *(t_sector **)map_get_index(env->current_map->sectors, i);
		walls = sector->walls.items;
		j = (size_t)-1;
		while (++j < sector->walls.total)
		{
			if (point->id == walls[j].v1->id)
			{
				if (sector->walls.total == 3)
				{
					ft_printf("Sector %lu is a triangle.\n", sector->id);
					return (false);
				}
			}
		}
	}
	return (true);
}

static void	free_wall_internal(t_vector *tmp_handler)
{
	size_t		i;
	t_deletion	*del;

	del = tmp_handler->items;
	i = 0;
	while (i < tmp_handler->total)
	{
		free_wall_event(del[i].wall1);
		free_wall_event(del[i].wall2);
		++i;
	}
}

int			delete_point(t_env *env, t_point *point, bool record)
{
	size_t		i;
	t_sector	*sector;
	t_vector	tmp_handler;
	int			ret;

	i = (size_t)-1;
	if (!verify_sector_triangle(point, env))
		return (0);
	if (!vector_init(&tmp_handler, sizeof(t_deletion)))
		return (-1);
	while (++i < point->sector->total)
	{
		sector = *(t_sector **)map_get_index(point->sector, i);
		ret = remove_point_from_sector(point, sector, &tmp_handler, env);
		if (ret != 1)
			return (ret);
	}
	if (record)
	{
		if (!delete_point_event(env, &tmp_handler, point))
			return (free_tmp_handler(point, env, &tmp_handler, -1));
	}
	else
		free_wall_internal(&tmp_handler);
	return (free_tmp_handler(point, env, &tmp_handler, 1));
}
