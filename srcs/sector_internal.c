/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_internal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:30:50 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 12:52:27 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		set_null_materials(t_vector *walls)
{
	size_t	i;
	t_wall	*tmp_wall;

	tmp_wall = walls->items;
	i = 0;
	while (i < walls->total)
	{
		tmp_wall[i].mtl_bottom = NULL;
		tmp_wall[i].mtl_top = NULL;
		i++;
	}
}

bool		set_material_internal(t_wall *wall, t_wall *old_wall, size_t i)
{
	if (!(wall[i].mtl_bottom = mtl_clone(old_wall[i].mtl_bottom)))
		return (false);
	if (!(wall[i].mtl_top = mtl_clone(old_wall[i].mtl_top)))
		return (false);
	return (true);
}

void		set_wall_point(t_wall *wall, t_vector *new_walls,
	t_point **point_array, size_t i)
{
	if (i == new_walls->total - 1)
	{
		wall[i].v1 = point_array[i];
		wall[i].v2 = point_array[0];
	}
	else
	{
		wall[i].v1 = point_array[i];
		wall[i].v2 = point_array[i + 1];
	}
}

static bool	internal_point_free(t_vector *vertices)
{
	t_point	**tmp_point;
	size_t	i;

	tmp_point = vertices->items;
	i = 0;
	while (i < vertices->total)
		point_free(tmp_point[i++]);
	return (false);
}

bool		internal_vertices_clone(t_sector *sector, t_vector *vertices)
{
	size_t		i;
	t_wall		*wall;
	t_point		*point;

	i = 0;
	wall = sector->walls.items;
	while (i < sector->walls.total)
	{
		if (!(point = point_clone(wall[i].v1)))
			break ;
		if (!vector_push(vertices, &point))
		{
			point_free(point);
			break ;
		}
		i++;
	}
	if (i < sector->walls.total)
		return (internal_point_free(vertices));
	return (true);
}
