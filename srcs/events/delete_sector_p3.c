/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sector_p3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:39:12 by thboura           #+#    #+#             */
/*   Updated: 2020/06/03 09:01:56 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
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
	if (!point_add_sector(wall->v1, sector))
	{
		free_all_point(points);
		return (false);
	}
	if (!map_add(points, (size_t)wall->v2, &wall->v2))
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
	return (true);
}

static bool	set_wall_neighbor(t_sector *sector, t_wall *wall, t_map *points)
{
	t_handler_struct	s;

	if (wall->neighbor == NULL)
		return (true);
	s.sectors = wall->neighbor;
	s.walls = s.sectors->walls.items;
	s.j = 0;
	while (s.j < s.sectors->walls.total)
	{
		if (s.walls[s.j].v1->v.v.x == wall->v2->v.v.x
			&& s.walls[s.j].v1->v.v.z == wall->v2->v.v.z
			&& s.walls[s.j].v2->v.v.x == wall->v1->v.v.x
			&& s.walls[s.j].v2->v.v.z == wall->v1->v.v.z)
			return (set_wall_neighbor_p2(wall, &s, sector, points));
		s.j++;
	}
	return (true);
}

bool		set_neighbor(t_sector *sector)
{
	t_handler_struct	s;
	t_map				*points;

	if (!(points = map_init(sizeof(t_point *))))
		return (false);
	s.i = 0;
	s.walls = sector->walls.items;
	while (s.i < sector->walls.total)
	{
		if (!set_wall_neighbor(sector, &s.walls[s.i], points))
			return (false);
		++s.i;
	}
	free_all_point(points);
	return (true);
}

t_point		*add_vertex2(t_point *v, t_sector *sector, t_env *env)
{
	t_point **point;

	if ((point = map_get(env->current_map->vertices, v->id)))
	{
		if (!map_add((*point)->sector, sector->id, &sector))
			return (NULL);
		return (*point);
	}
	v->v.v_texture.x = v->v.v.x;
	v->v.v_texture.y = v->v.v.z;
	if (!map_add(env->current_map->vertices, v->id, &v))
		return (NULL);
	if (!map_add(v->sector, sector->id, &sector))
		return (NULL);
	return (v);
}
