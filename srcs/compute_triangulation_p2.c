/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_triangulation_p2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:13:15 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 17:13:15 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangulation_internal.h"

bool	compute_triangulation_p5(t_vector new_polygon[2],
										t_vector *triangle)
{
	t_triangle	tri;

	tri.vertex[0] = (*(t_point **)vector_get(&new_polygon[0], 0))->v;
	tri.vertex[1] = (*(t_point **)vector_get(&new_polygon[0], 1))->v;
	tri.vertex[2] = (*(t_point **)vector_get(&new_polygon[0], 2))->v;
	vector_free(&new_polygon[0]);
	if (!vector_push(triangle, &tri))
	{
		vector_free(&new_polygon[1]);
		return (false);
	}
	return (true);
}
