/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulation_internal_p2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:10:27 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 00:11:53 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	set_top_triangle_texture(t_wall *wall)
{
	float	dist;

	dist = vec3f_dist(wall->triangle[0].vertex[0].v,
		wall->triangle[0].vertex[1].v);
	wall->triangle[0].vertex[0].v_texture.x = dist;
	wall->triangle[0].vertex[1].v_texture.x = 0;
	wall->triangle[0].vertex[2].v_texture.x = 0;
	dist = vec3f_dist(wall->triangle[1].vertex[2].v,
		wall->triangle[1].vertex[1].v);
	wall->triangle[1].vertex[0].v_texture.x = dist;
	wall->triangle[1].vertex[1].v_texture.x = 0;
	wall->triangle[1].vertex[2].v_texture.x = dist;
}

void		set_top_triangle(t_wall *wall, t_sector *sector)
{
	float	diff;

	diff = fabsf((sector->ceil + sector->floor)
		- (wall->neighbor->ceil + wall->neighbor->floor));
	wall->triangle[0].vertex[0].v = wall->v2->v.v;
	wall->triangle[0].vertex[0].v_texture.y = diff;
	wall->triangle[0].vertex[0].v.y += sector->ceil + sector->floor - diff;
	wall->triangle[0].vertex[1].v = wall->v1->v.v;
	wall->triangle[0].vertex[1].v_texture.y = diff;
	wall->triangle[0].vertex[1].v.y += sector->ceil + sector->floor - diff;
	wall->triangle[0].vertex[2].v = wall->v1->v.v;
	wall->triangle[0].vertex[2].v_texture.y = 0;
	wall->triangle[0].vertex[2].v.y += sector->ceil + sector->floor;
	wall->triangle[1].vertex[0].v = wall->v2->v.v;
	wall->triangle[1].vertex[0].v_texture.y = diff;
	wall->triangle[1].vertex[0].v.y += sector->ceil + sector->floor - diff;
	wall->triangle[1].vertex[1].v = wall->v1->v.v;
	wall->triangle[1].vertex[1].v_texture.y = 0;
	wall->triangle[1].vertex[1].v.y += sector->ceil + sector->floor;
	wall->triangle[1].vertex[2].v = wall->v2->v.v;
	wall->triangle[1].vertex[2].v_texture.y = 0;
	wall->triangle[1].vertex[2].v.y += sector->ceil + sector->floor;
	wall->wall_location |= WALL_TOP;
	set_top_triangle_texture(wall);
}

static void	set_bottom_triangle_texture(t_wall *wall)
{
	float	dist;

	dist = vec3f_dist(wall->triangle[2].vertex[1].v,
		wall->triangle[2].vertex[0].v);
	wall->triangle[2].vertex[0].v_texture.x = 0;
	wall->triangle[2].vertex[1].v_texture.x = dist;
	wall->triangle[2].vertex[2].v_texture.x = 0;
	dist = vec3f_dist(wall->triangle[3].vertex[2].v,
		wall->triangle[3].vertex[0].v);
	wall->triangle[3].vertex[0].v_texture.x = 0;
	wall->triangle[3].vertex[1].v_texture.x = dist;
	wall->triangle[3].vertex[2].v_texture.x = dist;
}

void		set_bottom_triangle(t_wall *wall, t_sector *sector)
{
	float	diff;

	diff = fabsf(sector->floor - wall->neighbor->floor);
	wall->triangle[2].vertex[1].v = wall->v2->v.v;
	wall->triangle[2].vertex[1].v_texture.y = diff;
	wall->triangle[2].vertex[1].v.y += sector->floor + diff;
	wall->triangle[2].vertex[0].v = wall->v1->v.v;
	wall->triangle[2].vertex[0].v_texture.y = diff;
	wall->triangle[2].vertex[0].v.y += sector->floor + diff;
	wall->triangle[2].vertex[2].v = wall->v1->v.v;
	wall->triangle[2].vertex[2].v_texture.y = 0;
	wall->triangle[2].vertex[2].v.y += sector->floor;
	wall->triangle[3].vertex[1].v = wall->v2->v.v;
	wall->triangle[3].vertex[1].v_texture.y = diff;
	wall->triangle[3].vertex[1].v.y += sector->floor + diff;
	wall->triangle[3].vertex[0].v = wall->v1->v.v;
	wall->triangle[3].vertex[0].v_texture.y = 0;
	wall->triangle[3].vertex[0].v.y += sector->floor;
	wall->triangle[3].vertex[2].v = wall->v2->v.v;
	wall->triangle[3].vertex[2].v_texture.y = 0;
	wall->triangle[3].vertex[2].v.y += sector->floor;
	wall->wall_location |= WALL_BOTTOM;
	set_bottom_triangle_texture(wall);
}
