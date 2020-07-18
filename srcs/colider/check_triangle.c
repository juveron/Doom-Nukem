/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:18:17 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 15:32:25 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collider.h"

static t_vec3f	get_normal(t_triangle *tri)
{
	t_vec3f normal;
	t_vec3f	line1;
	t_vec3f	line2;

	line1 = vec3f_sub(tri->vertex[1].v, tri->vertex[0].v);
	line2 = vec3f_sub(tri->vertex[2].v, tri->vertex[0].v);
	normal = vec3f_cross(line1, line2);
	normal = vec3f_normalize(normal);
	return (normal);
}

static void		set_closest(t_vec3f *closest, t_vec3f vec, float radius,
	float dist)
{
	*closest = vec3f_mul(vec, (radius - dist) / dist);
}

static int		capsule_triangle_check_p2(t_capsule_handler *handler,
	int i, t_vec3f *vec)
{
	int		j;
	float	tmp;

	j = 0;
	while (i--)
	{
		tmp = vec3f_length_sq(vec[i]);
		if (handler->dist > tmp)
		{
			j = i;
			handler->dist = tmp;
		}
	}
	handler->dist = sqrtf(handler->dist);
	return (j);
}

bool			capsule_triangle_check(t_vec3f *closest,
	t_capsule_collider *capsule, t_triangle *triangle)
{
	t_vec3f				vec[5];
	t_capsule_handler	handler;
	int					i;
	int					j;

	handler.normal = get_normal(triangle);
	i = 0;
	i += project_point_triangle(&vec[i], &capsule->start, triangle,
		&handler.normal);
	i += project_point_triangle(&vec[i], &capsule->end, triangle,
		&handler.normal);
	handler.dist = __FLT_MAX__;
	j = capsule_triangle_check_p2(&handler, i, vec);
	if (handler.dist < capsule->radius)
	{
		if (vec3f_dot(vec[j], handler.normal) < 0)
			set_closest(closest, vec[j], -capsule->radius, handler.dist);
		else
			set_closest(closest, vec[j], capsule->radius, handler.dist);
	}
	return (handler.dist < capsule->radius);
}
