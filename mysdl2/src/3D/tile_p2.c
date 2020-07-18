/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_p2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:45:54 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/07 13:45:54 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterizer.h"

float	edge_function_2(t_vec4f *a, t_vec4f *b, t_u16 x, t_u16 y)
{
	return ((x - a->x) * (b->y - a->y) - (y - a->y) * (b->x - a->x));
}

bool	check_if_inside_p2(t_triangle_raster *triangle, t_tile *tile,
		t_u16 *tmp)
{
	*tmp |= edge_function_2(&triangle->vertex[2].v, &triangle->vertex[0].v,
			tile->x_min, tile->y_min) > 0 << 8;
	*tmp |= edge_function_2(&triangle->vertex[2].v, &triangle->vertex[0].v,
			tile->x_max, tile->y_min) > 0 << 9;
	*tmp |= edge_function_2(&triangle->vertex[2].v, &triangle->vertex[0].v,
			tile->x_min, tile->y_max) > 0 << 10;
	*tmp |= edge_function_2(&triangle->vertex[2].v, &triangle->vertex[0].v,
			tile->x_max, tile->y_max) > 0 << 11;
	if ((*tmp >> 8 & 0x7) != 0 && (*tmp >> 8 & 0x7) != 0x7)
		return (1);
	if ((*tmp & 0xFFF) == 0xFFF)
		return (1);
	return (0);
}

bool	check_if_inside(t_triangle_raster *triangle, t_tile *tile)
{
	t_u16	tmp;

	tmp = 0;
	tmp |= edge_function_2(&triangle->vertex[0].v, &triangle->vertex[1].v,
		tile->x_min, tile->y_min) > 0 << 0;
	tmp |= edge_function_2(&triangle->vertex[0].v, &triangle->vertex[1].v,
		tile->x_max, tile->y_min) > 0 << 1;
	tmp |= edge_function_2(&triangle->vertex[0].v, &triangle->vertex[1].v,
		tile->x_min, tile->y_max) > 0 << 2;
	tmp |= edge_function_2(&triangle->vertex[0].v, &triangle->vertex[1].v,
		tile->x_max, tile->y_max) > 0 << 3;
	if ((tmp & 0x7) != 0 && (tmp & 0x7) != 0x7)
		return (1);
	tmp |= edge_function_2(&triangle->vertex[1].v, &triangle->vertex[2].v,
		tile->x_min, tile->y_min) > 0 << 4;
	tmp |= edge_function_2(&triangle->vertex[1].v, &triangle->vertex[2].v,
		tile->x_max, tile->y_min) > 0 << 5;
	tmp |= edge_function_2(&triangle->vertex[1].v, &triangle->vertex[2].v,
		tile->x_min, tile->y_max) > 0 << 6;
	tmp |= edge_function_2(&triangle->vertex[1].v, &triangle->vertex[2].v,
		tile->x_max, tile->y_max) > 0 << 7;
	if ((tmp >> 4 & 0x7) != 0 && (tmp >> 4 & 0x7) != 0x7)
		return (1);
	return (check_if_inside_p2(triangle, tile, &tmp));
}
