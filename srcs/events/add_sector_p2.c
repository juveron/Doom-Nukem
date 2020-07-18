/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sector_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 10:18:39 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 20:02:19 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	erase_neighbor(t_sector *sector)
{
	size_t	i;
	t_wall	*wall;

	wall = sector->walls.items;
	i = 0;
	while (i < sector->walls.total)
	{
		wall[i].neighbor = NULL;
		++i;
	}
}

static void	erase_wall_material(t_sector *sector)
{
	size_t	i;
	t_wall	*walls;

	i = 0;
	walls = sector->walls.items;
	while (i < sector->walls.total)
	{
		mtl_destroy(&walls[i].mtl_top);
		mtl_destroy(&walls[i].mtl_bottom);
		++i;
	}
}

bool		undo_sector(t_env *env, void *param)
{
	t_sector				*sector;
	t_rec_add_sector_event	*tmp_editor;

	tmp_editor = param;
	sector = *(t_sector **)map_get_index(env->current_map->sectors,
		env->current_map->sectors->total - 1);
	if (env->gui.status == GUI_SECTOR && sector == env->gui.sector_menu.sector)
		return (true);
	if (delete_sector(sector, env) == (size_t)-1
		|| !(env->editor.tmp_sector = sector_clone(tmp_editor->sector,
		&env->editor.tmp_vertices)))
		return (false);
	erase_wall_material(env->editor.tmp_sector);
	erase_neighbor(env->editor.tmp_sector);
	if (!change_selection_mode(env, EDITOR_SELECT_LINE))
		return (false);
	env->editor.state.global_state = EDITOR_MAKE_SECTOR;
	send_notify("Unclosed last sector.", 0xFFFFFF, env);
	return (true);
}
