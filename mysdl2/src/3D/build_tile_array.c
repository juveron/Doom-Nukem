/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tile_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:01:57 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/07 13:01:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

static bool	init_tile_array(t_context_3d *context_3d)
{
	context_3d->render_screen.tile_x = ceilf((float)WIDTH_
		/ (float)TILE_SIZE);
	context_3d->render_screen.tile_y = ceilf((float)HEIGHT_
		/ (float)TILE_SIZE);
	if (!(context_3d->render_screen.tiles = ft_memalloc(sizeof(t_tile)
		* context_3d->render_screen.tile_x * context_3d->render_screen.tile_y)))
		return (false);
	context_3d->tile_max = context_3d->render_screen.tile_x
		* context_3d->render_screen.tile_y;
	return (true);
}

static bool	set_tile_size(t_context_3d *context_3d, size_t i, size_t j)
{
	t_tile	*tile;

	tile = &context_3d->render_screen.tiles[j
		* context_3d->render_screen.tile_x + i];
	tile->x_min = i * TILE_SIZE;
	tile->y_min = j * TILE_SIZE;
	tile->x_max = (i + 1) * TILE_SIZE;
	tile->y_max = (j + 1) * TILE_SIZE;
	if (tile->x_max > WIDTH_)
		tile->x_max = WIDTH_;
	if (tile->y_max > HEIGHT_)
		tile->y_max = HEIGHT_;
	if (!vector_init(&tile->triangle_array, sizeof(t_triangle_raster)))
		return (false);
	return (true);
}

bool		build_tile_array(void)
{
	t_context_3d	*context_3d;
	size_t			i;
	size_t			j;

	context_3d = get_context()->context_3d;
	if (!init_tile_array(context_3d))
		return (false);
	j = 0;
	while (j < context_3d->render_screen.tile_y)
	{
		i = 0;
		while (i < context_3d->render_screen.tile_x)
		{
			if (!set_tile_size(context_3d, i, j))
			{
				free_tiles_array();
				return (false);
			}
			++i;
		}
		++j;
	}
	return (true);
}

void		free_tiles_array(void)
{
	t_context_3d	*context_3d;
	size_t			i;
	size_t			j;
	t_tile			*tile;

	context_3d = get_context()->context_3d;
	if (!context_3d->render_screen.tiles)
		return ;
	j = 0;
	while (j < context_3d->render_screen.tile_y)
	{
		i = 0;
		while (i < context_3d->render_screen.tile_x)
		{
			tile = &context_3d->render_screen.tiles[j
					* context_3d->render_screen.tile_x + i];
			vector_free(&tile->triangle_array);
			i++;
		}
		j++;
	}
	free(context_3d->render_screen.tiles);
}
