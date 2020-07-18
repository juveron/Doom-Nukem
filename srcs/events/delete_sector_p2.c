/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sector_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:39:12 by thboura           #+#    #+#             */
/*   Updated: 2020/06/03 09:01:40 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delete_sector_internal.h"

static void	internal_set_vertex_p2(t_handler_struct *s, t_sector *sector)
{
	s->walls[s->i].v1 = s->walls[get_correct_index(
			sector->walls.total, s->i - 1)].v2;
	s->walls[s->i].v2 = s->walls[0].v1;
}

static bool	internal_set_vertex_p3(t_handler_struct *s, t_sector *sector,
	t_env *env)
{
	if (s->walls[get_correct_index(
		sector->walls.total, s->i - 1)].neighbor != NULL)
		s->walls[s->i].v1 = s->walls[get_correct_index(
			sector->walls.total, s->i - 1)].v2;
	else
	{
		if (!(s->walls[s->i].v1 = add_vertex2(s->walls[s->i].v1, sector, env)))
			return (false);
	}
	if (s->walls[get_correct_index(sector->walls.total,
		s->i + 1)].neighbor != NULL)
		s->walls[s->i].v2 = s->walls[get_correct_index(
			sector->walls.total, s->i + 1)].v1;
	else
	{
		if (!(s->walls[s->i].v2 = add_vertex2(s->walls[s->i].v2, sector, env)))
			return (false);
	}
	return (true);
}

bool		internal_set_vertex(t_handler_struct *s, t_sector *sector,
	t_env *env)
{
	if (s->i == sector->walls.total - 1)
		internal_set_vertex_p2(s, sector);
	else if (s->walls[s->i].neighbor == NULL)
		return (internal_set_vertex_p3(s, sector, env));
	return (true);
}

static bool	set_vertex_sector2(t_sector *sector, t_env *env)
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

bool		convert_sector2(t_sector *sector, t_vector *vertices, t_env *env)
{
	if (!set_neighbor(sector))
		return (false);
	if (!set_vertex_sector2(sector, env))
		return (false);
	vector_free(vertices);
	if (!map_add(env->current_map->sectors, sector->id,
		&sector))
		return (false);
	if (!triangulate_sector(sector))
		return (false);
	return (true);
}
