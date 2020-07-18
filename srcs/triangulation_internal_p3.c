/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulation_internal_p3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:12:15 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 00:14:43 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	set_full_triangle_texture(t_wall *wall)
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

void		set_full_triangle(t_wall *wall, t_sector *sector)
{
	wall->wall_location = 0;
	wall->triangle[0].vertex[0].v = wall->v2->v.v;
	wall->triangle[0].vertex[0].v_texture.y = 0;
	wall->triangle[0].vertex[0].v.y += sector->floor;
	wall->triangle[0].vertex[1].v = wall->v1->v.v;
	wall->triangle[0].vertex[1].v_texture.y = 0;
	wall->triangle[0].vertex[1].v.y += sector->floor;
	wall->triangle[0].vertex[2].v = wall->v1->v.v;
	wall->triangle[0].vertex[2].v_texture.y = sector->ceil;
	wall->triangle[0].vertex[2].v.y += sector->floor + sector->ceil;
	wall->triangle[1].vertex[0].v = wall->v2->v.v;
	wall->triangle[1].vertex[0].v_texture.y = 0;
	wall->triangle[1].vertex[0].v.y += sector->floor;
	wall->triangle[1].vertex[1].v = wall->v1->v.v;
	wall->triangle[1].vertex[1].v_texture.y = sector->ceil;
	wall->triangle[1].vertex[1].v.y += sector->floor + sector->ceil;
	wall->triangle[1].vertex[2].v = wall->v2->v.v;
	wall->triangle[1].vertex[2].v_texture.y = sector->ceil;
	wall->triangle[1].vertex[2].v.y += sector->floor + sector->ceil;
	set_full_triangle_texture(wall);
}

void		flip_triangle(t_triangle *triangle)
{
	t_vertex tmp;

	tmp = triangle->vertex[1];
	triangle->vertex[1] = triangle->vertex[2];
	triangle->vertex[2] = tmp;
}
