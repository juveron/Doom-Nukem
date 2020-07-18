/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 12:39:54 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 12:40:31 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collider.h"

static float	dist_point_plane(const t_vec3f *plane_normal,
	const t_vec3f *plane_origin, const t_vec3f *point)
{
	return (vec3f_dot(vec3f_sub(*point, *plane_origin), *plane_normal));
}

bool			project_point_triangle(t_vec3f *proj, const t_vec3f *point,
	const t_triangle *triangle, const t_vec3f *normal)
{
	float	d;
	float	dot[3];
	t_vec3f	tmp;

	d = vec3f_dot(vec3f_sub(*point, triangle->vertex[0].v), *normal);
	*proj = vec3f_sub(*point, vec3f_mul(*normal, d));
	tmp = vec3f_cross(vec3f_sub(triangle->vertex[1].v, triangle->vertex[0].v),
		*normal);
	dot[0] = dist_point_plane(&tmp, &triangle->vertex[0].v, proj);
	tmp = vec3f_cross(vec3f_sub(triangle->vertex[2].v, triangle->vertex[1].v),
		*normal);
	dot[1] = dist_point_plane(&tmp, &triangle->vertex[1].v, proj);
	tmp = vec3f_cross(vec3f_sub(triangle->vertex[0].v, triangle->vertex[2].v),
		*normal);
	dot[2] = dist_point_plane(&tmp, &triangle->vertex[2].v, proj);
	*proj = vec3f_sub(*point, *proj);
	return (dot[0] <= 0.f && dot[1] <= 0.f && dot[2] <= 0.f);
}
