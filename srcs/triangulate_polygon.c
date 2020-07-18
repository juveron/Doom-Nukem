/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate_polygon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:29:37 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 16:17:53 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangulation_internal.h"

static void	triangulate_wall(t_sector *sector)
{
	size_t	i;
	t_wall	*walls;

	walls = sector->walls.items;
	i = 0;
	while (i < sector->walls.total)
	{
		if (walls[i].neighbor != NULL)
		{
			walls[i].wall_location = 0;
			if (walls[i].neighbor->ceil + walls[i].neighbor->floor
				< sector->ceil + sector->floor)
				set_top_triangle(&walls[i], sector);
			if (walls[i].neighbor->floor > sector->floor)
				set_bottom_triangle(&walls[i], sector);
			if (walls[i].wall_location == 0)
			{
				walls[i].wall_location = WALL_PORTAL;
			}
		}
		else
			set_full_triangle(&walls[i], sector);
		i++;
	}
}

static void	set_ceil_triangle(t_sector *sector)
{
	size_t		i;
	t_triangle	*triangle;

	i = 0;
	triangle = sector->triangle_top.items;
	while (i < sector->triangle_top.total)
	{
		triangle[i].vertex[0].v.y += sector->ceil;
		triangle[i].vertex[1].v.y += sector->ceil;
		triangle[i].vertex[2].v.y += sector->ceil;
		flip_triangle(&triangle[i]);
		i++;
	}
}

static void	set_floor_triangle(t_sector *sector)
{
	size_t		i;
	t_triangle	*triangle;

	i = 0;
	triangle = sector->triangle_bottom.items;
	while (i < sector->triangle_bottom.total)
	{
		triangle[i].vertex[0].v.y += sector->floor;
		triangle[i].vertex[1].v.y += sector->floor;
		triangle[i].vertex[2].v.y += sector->floor;
		i++;
	}
}

static bool	triangulate_sector_p2(t_sector *sector, t_vector *polygon,
	t_vector *triangle)
{
	if (!compute_triangulation(polygon, triangle))
	{
		vector_free(polygon);
		vector_free(triangle);
		return (false);
	}
	triangulate_wall(sector);
	if (sector->triangle_bottom.items != NULL)
		vector_free(&sector->triangle_bottom);
	sector->triangle_bottom = *triangle;
	set_floor_triangle(sector);
	if (sector->has_roof)
	{
		if (sector->triangle_top.items != NULL)
			vector_free(&sector->triangle_top);
		if (!vector_clone(triangle, &sector->triangle_top))
			return (false);
		set_ceil_triangle(sector);
	}
	vector_free(polygon);
	return (set_material(sector));
}

bool		triangulate_sector(t_sector *sector)
{
	t_vector	triangle;
	t_vector	polygon;
	t_wall		*wall;
	t_point		**p_point;
	size_t		i;

	if (!sector || !vector_init(&triangle, sizeof(t_triangle)))
		return (false);
	if (!vector_init_n(&polygon, sizeof(t_point *), sector->walls.total))
	{
		vector_free(&triangle);
		return (false);
	}
	wall = sector->walls.items;
	p_point = polygon.items;
	i = 0;
	init_aabb(&sector->aabb);
	while (i < sector->walls.total)
	{
		p_point[i] = wall[i].v1;
		update_aabb(&sector->aabb, &wall[i].v1->v.v);
		i++;
	}
	return (triangulate_sector_p2(sector, &polygon, &triangle));
}
