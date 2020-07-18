/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:42:55 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 15:24:57 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector_internal.h"

static bool	free_walls_return(t_vector *walls)
{
	free_walls_sector(walls);
	return (false);
}

bool		wall_clone_internal(t_vector *new_vertices,
	t_vector *new_walls, t_vector *tmp_wall)
{
	t_point	**point_array2;
	t_wall	*wall;
	t_wall	*old_wall;
	size_t	i;

	if (!vector_clone(tmp_wall, new_walls))
		return (false);
	set_null_materials(new_walls);
	old_wall = tmp_wall->items;
	point_array2 = new_vertices->items;
	wall = new_walls->items;
	i = 0;
	while (i < new_walls->total)
	{
		set_wall_point(wall, new_walls, point_array2, i);
		if (wall[i].neighbor == NULL)
			wall[i].neighbor = (t_sector *)-1;
		else
			wall[i].neighbor = (t_sector *)wall[i].neighbor->id;
		if (!set_material_internal(wall, old_wall, i++))
			return (free_walls_return(new_walls));
	}
	return (true);
}

t_sector	*sector_clone(t_sector *sector, t_vector *vertices)
{
	t_sector	*clone;

	if (!(clone = ft_memalloc(sizeof(t_sector))))
		return (NULL);
	if (!vector_init(vertices, sizeof(t_point *)))
	{
		free(clone);
		return (NULL);
	}
	*clone = *sector;
	clone->mtl_ceil = NULL;
	clone->mtl_floor = NULL;
	clone->triangle_bottom.items = NULL;
	clone->triangle_top.items = NULL;
	if (!internal_vertices_clone(sector, vertices)
		|| !wall_clone_internal(vertices, &clone->walls, &sector->walls))
	{
		free(clone);
		vector_free(vertices);
		return (NULL);
	}
	return (clone);
}
