/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pvs_p4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:57:51 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 15:57:52 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	copy_pvs(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2)
{
	pvs2->wall = pvs->wall_i;
	pvs2->vector = pvs->vector;
	pvs2->sector = pvs->wall_i->neighbor;
}

t_vec2f	vec3_to_vec2(t_vec3f *v)
{
	return (vec2f(v->x, v->z));
}

t_vec3f	vec2_to_vec3(t_vec2f v)
{
	return (vec3f(v.x, 0, v.y));
}

t_vec2f	line_line_intersect(t_vec2f a, t_vec2f b, t_vec2f c, t_vec2f d)
{
	t_vec2f	l1;
	t_vec2f	l2;
	t_vec2f	l3;
	float	det;

	l1 = vec2f(b.y - a.y, d.y - c.y);
	l2 = vec2f(a.x - b.x, c.x - d.x);
	l3 = vec2f(l1.x * a.x + l2.x * a.y, l1.y * c.x + l2.y * c.y);
	det = vec2f_cross(l1, l2);
	if (det == 0.f)
	{
		return (vec2f(__FLT_MAX__, __FLT_MAX__));
	}
	else
	{
		return (vec2f(vec2f_cross(l3, l2) / det, vec2f_cross(l1, l3) / det));
	}
}

float	vec3f_cross_v2(t_vec3f vec1, t_vec3f vec2)
{
	return (-vec1.z * vec2.x - vec1.x * -vec2.z);
}
