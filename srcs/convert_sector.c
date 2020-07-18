/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_sector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 10:29:24 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/19 12:30:31 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	free_all_point(t_map *map)
{
	size_t	i;
	t_point	*point;

	i = 0;
	while (i < map->total)
	{
		point = *(t_point **)map_get_index(map, i);
		free_point(point);
		++i;
	}
	map_free(map);
}

static bool	set_wall_neighbor_p2(t_wall *wall, t_handler_struct *s,
	t_sector *sector, t_map *points)
{
	wall->neighbor = s->sectors;
	if (!map_add(points, (size_t)wall->v1, &wall->v1))
	{
		free_all_point(points);
		return (false);
	}
	wall->v1 = s->walls[s->j].v2;
	if (!point_add_sector(wall->v1, sector)
		|| !map_add(points, (size_t)wall->v2, &wall->v2))
	{
		free_all_point(points);
		return (false);
	}
	wall->v2 = s->walls[s->j].v1;
	if (!point_add_sector(wall->v2, sector))
	{
		free_all_point(points);
		return (false);
	}
	s->walls[s->j].neighbor = sector;
	sector->floor = s->sectors->floor;
	sector->ceil = s->sectors->ceil;
	return (true);
}

static bool	set_wall_neighbor(t_sector *sector, t_wall *wall, t_env *env,
	t_map *points)
{
	t_handler_struct	s;

	s.i = 0;
	while (s.i < env->current_map->sectors->total)
	{
		s.sectors = *(t_sector **)map_get_index(env->current_map->sectors, s.i);
		s.walls = s.sectors->walls.items;
		s.j = 0;
		while (s.j < s.sectors->walls.total)
		{
			if ((s.walls[s.j].v1->v.v.x == wall->v2->v.v.x
				&& s.walls[s.j].v1->v.v.z == wall->v2->v.v.z
				&& s.walls[s.j].v2->v.v.x == wall->v1->v.v.x
				&& s.walls[s.j].v2->v.v.z == wall->v1->v.v.z))
				return (set_wall_neighbor_p2(wall, &s, sector, points));
			s.j++;
		}
		s.i++;
	}
	wall->neighbor = NULL;
	return (true);
}

static bool	set_neighbor(t_sector *sector, t_env *env)
{
	t_handler_struct	s;
	t_map				*points;

	if (!(points = map_init(sizeof(t_point *))))
		return (false);
	s.i = 0;
	s.walls = sector->walls.items;
	while (s.i < sector->walls.total)
	{
		if (!set_wall_neighbor(sector, &s.walls[s.i], env, points))
			return (false);
		++s.i;
	}
	free_all_point(points);
	return (true);
}

bool		convert_sector(t_sector *sector, t_vector *vertices, t_env *env)
{
	if (!clockwise_dir(sector))
		flip_wall(sector, env);
	sector->ceil = 3;
	sector->floor = 0;
	sector->has_roof = true;
	if (!set_neighbor(sector, env))
		return (false);
	if (!set_vertex_sector(sector, env))
		return (false);
	vector_free(vertices);
	if (!map_add(env->current_map->sectors, sector->id,
		&sector))
		return (false);
	if (!triangulate_sector(sector)
		|| !triangulate_all_neighbor(sector))
		return (false);
	return (true);
}
