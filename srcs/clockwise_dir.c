/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clockwise_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 08:51:50 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/07 17:39:48 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	clockwise_ret(size_t index, t_wall *walls, size_t size)
{
	t_vec3f	v0;
	t_vec3f	v1;
	t_vec3f	v2;
	float	tmp;

	v0 = walls[index].v1->v.v;
	v1 = walls[index].v2->v.v;
	v2 = walls[(index + 1) % size].v2->v.v;
	if (v2.z <= v1.z && v1.z <= v0.z)
		return (0);
	if (v0.z <= v1.z && v1.z <= v2.z)
		return (1);
	tmp = (v0.x - v1.x) * (v2.z - v1.z) - (v2.x - v1.x) * (v0.z - v1.z);
	if (tmp < 0)
		return (0);
	else
		return (1);
}

int			clockwise_dir(t_sector *sector)
{
	t_handler_struct	s;
	size_t				index;
	float				minx;

	minx = __FLT_MAX__;
	s.walls = sector->walls.items;
	s.i = 0;
	while (s.i < sector->walls.total)
	{
		if (s.walls[s.i].v2->v.v.x < minx)
		{
			minx = s.walls[s.i].v2->v.v.x;
			index = s.i;
		}
		s.i++;
	}
	return (clockwise_ret(index, s.walls, sector->walls.total));
}
