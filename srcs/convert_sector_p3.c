/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_sector_p3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 10:29:24 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 18:12:26 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	set_material_sector(t_sector *sector)
{
	if (!sector->mtl_ceil)
	{
		if (!(sector->mtl_ceil = mtl_create()))
			return (false);
		mtl_change_diffuse_color(sector->mtl_ceil, get_random_color());
	}
	if (!sector->mtl_floor)
	{
		if (!(sector->mtl_floor = mtl_create()))
			return (false);
		mtl_change_diffuse_color(sector->mtl_floor, get_random_color());
	}
	return (true);
}

bool		set_material(t_sector *sector)
{
	size_t	i;
	t_wall	*walls;

	if (!set_material_sector(sector))
		return (false);
	walls = sector->walls.items;
	i = 0;
	while (i < sector->walls.total)
	{
		if (!walls[i].mtl_top)
		{
			if (!(walls[i].mtl_top = mtl_create()))
				return (false);
			mtl_change_diffuse_color(walls[i].mtl_top, get_random_color());
		}
		if (!walls[i].mtl_bottom)
		{
			if (!(walls[i].mtl_bottom = mtl_create()))
				return (false);
			mtl_change_diffuse_color(walls[i].mtl_bottom, get_random_color());
		}
		i++;
	}
	return (true);
}
