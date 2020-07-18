/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_sector_p2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 10:44:53 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/19 12:29:36 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	add_vertex2(t_point *v, t_sector *sector, t_env *env)
{
	v->v.v_texture.x = v->v.v.x;
	v->v.v_texture.y = v->v.v.z;
	if (!map_add(env->current_map->vertices, v->id, &v))
		return (false);
	if (!map_add(v->sector, sector->id, &sector))
		return (false);
	return (true);
}

static void	internal_set_vertex2(t_handler_struct *s, t_sector *sector)
{
	s->walls[s->i].v1 = s->walls[get_correct_index(
			sector->walls.total, s->i - 1)].v2;
	s->walls[s->i].v2 = s->walls[0].v1;
}

static bool	internal_set_vertex(t_handler_struct *s, t_sector *sector,
	t_env *env)
{
	if (s->i == sector->walls.total - 1)
		internal_set_vertex2(s, sector);
	else if (s->walls[s->i].neighbor == NULL)
	{
		if (s->walls[get_correct_index(
			sector->walls.total, s->i - 1)].neighbor != NULL)
		{
			s->walls[s->i].v1 = s->walls[get_correct_index(
				sector->walls.total, s->i - 1)].v2;
		}
		else if (!add_vertex2(s->walls[s->i].v1, sector, env))
			return (false);
		if (s->walls[get_correct_index(sector->walls.total,
			s->i + 1)].neighbor != NULL)
		{
			s->walls[s->i].v2 = s->walls[get_correct_index(
				sector->walls.total, s->i + 1)].v1;
		}
		else if (!add_vertex2(s->walls[s->i].v2, sector, env))
			return (false);
	}
	return (true);
}

bool		set_vertex_sector(t_sector *sector, t_env *env)
{
	t_handler_struct	s;

	s.walls = sector->walls.items;
	s.i = 0;
	while (s.i < sector->walls.total)
	{
		if (!internal_set_vertex(&s, sector, env))
			return (false);
		s.i++;
	}
	return (true);
}
