/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulation_internal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 23:04:03 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 15:44:49 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "internal_handler.h"

t_u64			get_most_left_vertex(t_vector *polygon)
{
	t_vec3f	left;
	t_point	**vertex;
	size_t	i;
	t_u64	index_left;

	vertex = polygon->items;
	left = vertex[0]->v.v;
	index_left = 0;
	i = 1;
	while (i < polygon->total)
	{
		if (vertex[i]->v.v.x <= left.x)
		{
			if (!(vertex[i]->v.v.x == left.x && vertex[i]->v.v.z > left.z))
			{
				left = vertex[i]->v.v;
				index_left = i;
			}
		}
		i++;
	}
	return (index_left);
}

static float	line_equation(t_vec3f *vec0, t_vec3f *vec1, t_vec3f *vec2)
{
	return ((vec1->z - vec0->z) * (vec2->x - vec0->x)
		- (vec1->x - vec0->x) * (vec2->z - vec0->z));
}

static bool		point_in_triangle(t_u32 *points, t_point *a,
	t_point **polygon)
{
	float	val1;
	float	val2;
	float	val3;

	val1 = line_equation(&polygon[points[0]]->v.v, &polygon[points[1]]->v.v,
		&a->v.v);
	val2 = line_equation(&polygon[points[1]]->v.v, &polygon[points[2]]->v.v,
		&a->v.v);
	val3 = line_equation(&polygon[points[2]]->v.v, &polygon[points[0]]->v.v,
		&a->v.v);
	return (val1 >= 0 && val2 >= 0 && val3 >= 0);
}

static void		check_polygon(t_vector *polygon, t_farthest_handler *handler,
	t_u32 *index, size_t i)
{
	if (i != index[0] && i != index[1] && i != index[2])
	{
		if (point_in_triangle(index, *(t_point **)vector_get(polygon, i),
			polygon->items))
		{
			handler->d = fabsf(line_equation(&(*(t_point **)vector_get(polygon,
				index[1]))->v.v, &(*(t_point **)vector_get(polygon,
				index[2]))->v.v, &(*(t_point **)vector_get(polygon, i))->v.v));
			if (handler->distance < handler->d)
			{
				handler->distance = handler->d;
				handler->return_value = i;
			}
		}
	}
}

t_u32			get_farthest_vertex(t_vector *polygon, t_u64 left)
{
	t_farthest_handler	handler;
	t_u32				index[3];
	size_t				i;

	index[0] = left;
	index[1] = get_correct_index(polygon->total, left + 1);
	index[2] = get_correct_index(polygon->total, left - 1);
	handler.distance = -1;
	handler.return_value = left;
	i = 0;
	while (i < polygon->total)
		check_polygon(polygon, &handler, index, i++);
	return (handler.return_value);
}
