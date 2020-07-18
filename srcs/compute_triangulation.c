/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_triangulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 23:15:36 by thboura           #+#    #+#             */
/*   Updated: 2020/06/16 14:49:23 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangulation_internal.h"

static bool	make_new_polygon(t_vector *new_polygon, t_vector *polygon,
	t_u32 start, t_u32 end)
{
	size_t		i;

	if (!vector_init(new_polygon, sizeof(t_point *)))
		return (false);
	i = start;
	while (i != end)
	{
		if (!vector_push(new_polygon, vector_get(polygon, i)))
		{
			vector_free(new_polygon);
			return (false);
		}
		i = get_correct_index(polygon->total, i + 1);
	}
	if (!vector_push(new_polygon, vector_get(polygon, i)))
	{
		vector_free(new_polygon);
		return (false);
	}
	return (true);
}

static bool	compute_triangulation_p4(t_vector *new_polygon,
	t_vector *triangle)
{
	t_triangle	tri;

	if (new_polygon[1].total == 3)
	{
		tri.vertex[0] = (*(t_point **)vector_get(&new_polygon[1], 0))->v;
		tri.vertex[1] = (*(t_point **)vector_get(&new_polygon[1], 1))->v;
		tri.vertex[2] = (*(t_point **)vector_get(&new_polygon[1], 2))->v;
		vector_free(&new_polygon[1]);
		if (!vector_push(triangle, &tri))
			return (false);
	}
	else
	{
		if (!compute_triangulation(&new_polygon[1], triangle))
			return (false);
	}
	return (true);
}

static bool	compute_triangulation_p3(t_vector *polygon, t_u64 j0, t_u64 j,
	t_vector *triangle)
{
	t_vector	new_polygon[2];

	if (!make_new_polygon(&new_polygon[0], polygon, j0, j)
		|| !make_new_polygon(&new_polygon[1], polygon, j, j0))
	{
		vector_free(polygon);
		vector_free(&new_polygon[0]);
		return (false);
	}
	vector_free(polygon);
	if (new_polygon[0].total == 3)
	{
		if (!compute_triangulation_p5(new_polygon, triangle))
			return (false);
	}
	else
	{
		if (!compute_triangulation(&new_polygon[0], triangle))
			return (false);
	}
	return (compute_triangulation_p4(new_polygon, triangle));
}

static bool	compute_triangulation_p2(t_vector *polygon, t_u64 j0,
	t_vector *triangle)
{
	t_point		**point;
	t_triangle	tri;

	point = polygon->items;
	tri.vertex[0] = point[j0]->v;
	tri.vertex[1] = point[get_correct_index(polygon->total, j0 + 1)]->v;
	tri.vertex[2] = point[get_correct_index(polygon->total, j0 - 1)]->v;
	if (!vector_push(triangle, &tri))
		return (false);
	if (!vector_delete(polygon, j0))
		return (false);
	if (polygon->total < 3)
		return (true);
	else if (polygon->total == 3)
	{
		tri.vertex[0] = (*(t_point **)vector_get(polygon, 0))->v;
		tri.vertex[1] = (*(t_point **)vector_get(polygon, 1))->v;
		tri.vertex[2] = (*(t_point **)vector_get(polygon, 2))->v;
		if (!vector_push(triangle, &tri))
			return (false);
		vector_free(polygon);
	}
	else
		return (compute_triangulation(polygon, triangle));
	return (true);
}

bool		compute_triangulation(t_vector *polygon, t_vector *triangle)
{
	t_u64		j0;
	t_u64		j;

	j0 = get_most_left_vertex(polygon);
	j = get_farthest_vertex(polygon, j0);
	if (j == j0)
		return (compute_triangulation_p2(polygon, j0, triangle));
	else
		return (compute_triangulation_p3(polygon, j0, j, triangle));
}
