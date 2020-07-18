/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:21:21 by thboura           #+#    #+#             */
/*   Updated: 2020/07/14 10:30:14 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	init_wall_menu(t_wall *wall, bool top, t_env *env)
{
	if (env->gui.status != GUI_WALL)
	{
		if (!container_clear(env->gui.window->container)
			|| !container_add(env->gui.window->container,
				&env->gui.material_menu->container->component))
			return (false);
	}
	if (top)
	{
		if (!init_texture_menu(env->gui.material_menu, wall->mtl_top))
			return (false);
	}
	else
	{
		if (!init_texture_menu(env->gui.material_menu, wall->mtl_bottom))
			return (false);
	}
	env->gui.status = GUI_WALL;
	return (true);
}

bool	triangulate_all_neighbor(t_sector *sector)
{
	size_t	i;
	t_wall	*walls;

	i = 0;
	walls = sector->walls.items;
	while (i < sector->walls.total)
	{
		if (walls[i].neighbor)
			if (!triangulate_sector(walls[i].neighbor))
				return (false);
		++i;
	}
	return (true);
}
