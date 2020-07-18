/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:25:05 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/07 19:16:20 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	swap_vec3f(t_vec3f *v1, t_vec3f *v2)
{
	t_vec3f	tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

static bool	inside_p2(t_vec3f *tmp, t_vec3f *tmp2, t_vec2f *pos,
	bool *is_inside)
{
	float	a;
	float	b;

	if (tmp->x > tmp2->x)
		swap_vec3f(tmp, tmp2);
	if (tmp->x <= pos->x && tmp2->x >= pos->x
		&& tmp->z == tmp2->z && tmp->z == pos->y)
		return (false);
	if (tmp->z > tmp2->z)
		swap_vec3f(tmp, tmp2);
	if (tmp->z <= pos->y && pos->y < tmp2->z)
	{
		a = tmp->x * (pos->y - tmp2->z) + tmp2->x * (tmp->z - pos->y);
		b = pos->x * (tmp->z - tmp2->z);
		if (a == b)
			return (false);
		if (a < b)
			*is_inside ^= 1;
	}
	return (true);
}

bool		inside(t_vec2f *pos, t_sector *sector, bool edge)
{
	bool				is_inside;
	t_handler_struct	s;
	size_t				i;
	t_vec3f				tmp;
	t_vec3f				tmp2;

	i = (size_t)-1;
	is_inside = 0;
	s.walls = sector->walls.items;
	if (!inside_aabb(&sector->aabb, pos))
		return (false);
	while (++i < sector->walls.total)
	{
		tmp = s.walls[i].v1->v.v;
		tmp2 = s.walls[i].v2->v.v;
		if (tmp.z > tmp2.z)
			swap_vec3f(&tmp, &tmp2);
		if (tmp.x == tmp2.x && tmp.x == pos->x
			&& tmp.z <= pos->y && pos->y <= tmp2.z)
			return (edge);
		if (pos->x <= tmp.x || pos->x <= tmp2.x)
			if (!inside_p2(&tmp, &tmp2, pos, &is_inside))
				return (edge);
	}
	return (is_inside);
}
