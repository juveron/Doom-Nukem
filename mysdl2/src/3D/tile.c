/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:04:04 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/11 11:11:15 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"
#include "rasterizer.h"

void	init_bound(t_triangle_raster *triangle, t_vec2i *min_tile,
		t_vec2i *max_tile, t_context_3d *context_3d)
{
	t_vec2f			min;
	t_vec2f			max;

	min.x = fminf(triangle->vertex[0].v.x, fminf(triangle->vertex[1].v.x,
			triangle->vertex[2].v.x));
	min.y = fminf(triangle->vertex[0].v.y, fminf(triangle->vertex[1].v.y,
			triangle->vertex[2].v.y));
	max.x = fmaxf(triangle->vertex[0].v.x, fmaxf(triangle->vertex[1].v.x,
			triangle->vertex[2].v.x));
	max.y = fmaxf(triangle->vertex[0].v.y, fmaxf(triangle->vertex[1].v.y,
			triangle->vertex[2].v.y));
	min.x /= TILE_SIZE;
	min.y /= TILE_SIZE;
	max.x /= TILE_SIZE;
	max.y /= TILE_SIZE;
	min_tile->x = maxi(floorf(min.x), 0);
	min_tile->y = maxi(floorf(min.y), 0);
	max_tile->x = mini(ceilf(max.x), context_3d->render_screen.tile_x);
	max_tile->y = mini(ceilf(max.y), context_3d->render_screen.tile_y);
}

bool	add_to_tile(t_context_3d *context_3d, t_vec2i *pos,
		t_triangle_raster *triangle, t_material *material)
{
	t_tile *tile;

	tile = &context_3d->render_screen.tiles[pos->y
		* context_3d->render_screen.tile_x + pos->x];
	if (!check_if_inside(triangle, tile))
	{
		context_3d->n_tile_skiped++;
		return (true);
	}
	triangle->material = material;
	if (!vector_push(&tile->triangle_array, triangle))
		return (false);
	return (true);
}

bool	add_triangle_to_tiles(t_triangle_raster *triangle, t_material *material)
{
	t_context_3d	*context_3d;
	t_vec2i			min_tile;
	t_vec2i			max_tile;
	t_vec2i			pos;

	context_3d = get_context()->context_3d;
	init_bound(triangle, &min_tile, &max_tile, context_3d);
	pos.y = min_tile.y;
	while (pos.y < max_tile.y)
	{
		pos.x = min_tile.x;
		while (pos.x < max_tile.x)
		{
			if (!add_to_tile(context_3d, &pos, triangle, material))
				return (false);
			pos.x++;
		}
		pos.y++;
	}
	return (true);
}

bool	draw_tile(t_tile *tile)
{
	t_triangle_raster	*triangles;
	t_context_3d		*context_3d;
	size_t				i;

	context_3d = get_context()->context_3d;
	triangles = tile->triangle_array.items;
	i = 0;
	while (i < tile->triangle_array.total)
	{
		draw_triangle_tile(&triangles[i], tile, &context_3d->render_screen);
		i++;
	}
	vector_free(&tile->triangle_array);
	if (!vector_init(&tile->triangle_array, sizeof(t_triangle_raster)))
		return (false);
	return (true);
}
