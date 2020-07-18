/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flip_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:03:19 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 18:03:20 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	flip_wall(t_sector *sector, t_env *env)
{
	t_handler_struct	s;
	t_wall				tmp;
	t_wall				*walls;
	t_point				*point;

	s.i = 0;
	s.j = env->editor.tmp_vertices.total - 1;
	walls = sector->walls.items;
	while (s.i < s.j)
	{
		tmp = walls[s.i];
		walls[s.i].v1 = walls[s.j].v2;
		walls[s.i].v2 = walls[s.j].v1;
		walls[s.j].v2 = tmp.v1;
		walls[s.j].v1 = tmp.v2;
		s.i++;
		s.j--;
	}
	if (s.i == s.j)
	{
		point = walls[s.i].v2;
		walls[s.i].v2 = walls[s.i].v1;
		walls[s.i].v1 = point;
	}
}
