/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 10:18:39 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 16:22:11 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	redo_sector(t_env *env, void *param)
{
	t_wall		*walls;

	(void)param;
	walls = vector_get(&env->editor.tmp_sector->walls, 0);
	walls[env->editor.tmp_sector->walls.total - 1].v2 = walls[0].v1;
	if (!convert_sector(env->editor.tmp_sector, &env->editor.tmp_vertices, env))
		return (false);
	if (!set_material(env->editor.tmp_sector)
		|| !change_selection_mode(env, EDITOR_SELECT_LINE))
		return (false);
	env->editor.state.global_state = EDITOR_IDLE;
	send_notify("Reclosed last sector.", 0xFFFFFF, env);
	return (true);
}

static bool	delete_event(void *param)
{
	t_rec_add_sector_event *tmp;

	tmp = param;
	free_sector_event(tmp->sector, &tmp->vertices);
	free(tmp);
	return (false);
}

bool		add_sector_event(t_env *env)
{
	t_rec_add_sector_event	*tmp;

	if (!(tmp = (t_rec_add_sector_event *)ft_memalloc(sizeof(
		t_rec_add_sector_event))))
	{
		ft_printf("Could not record event.");
		return (false);
	}
	if (!set_material(env->editor.tmp_sector)
		|| !(tmp->sector = sector_clone(env->editor.tmp_sector,
		&tmp->vertices)))
		return (delete_event(tmp));
	remap_neighbor(tmp->sector, env);
	tmp->func.redo = &redo_sector;
	tmp->func.undo = &undo_sector;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_ADD_SECTOR, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
