/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:39:12 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 20:04:16 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delete_sector_internal.h"
#include "editor.h"

static bool	undo_sector_deletion(t_env *env, void *param)
{
	t_sector				*clone;
	t_vector				vertices;
	t_rec_del_sector_event	*tmp;

	tmp = param;
	if (!(clone = sector_clone2(tmp->sector, &vertices)))
		return (false);
	remap_neighbor(clone, env);
	if (!triangulate_sector(clone)
		|| !convert_sector2(clone, &vertices, env))
		return (false);
	return (true);
}

static bool	redo_sector_deletion(t_env *env, void *param)
{
	t_sector				*to_del;
	t_rec_del_sector_event	*tmp;

	tmp = param;
	to_del = *(t_sector **)map_get(env->current_map->sectors, tmp->sector->id);
	if (env->gui.status == GUI_SECTOR && to_del == env->gui.sector_menu.sector)
		return (false);
	if (delete_sector(to_del, env) == (size_t)-1)
		return (false);
	return (true);
}

static bool	delete_event(void *param)
{
	t_rec_del_sector_event	*tmp;

	tmp = param;
	free_sector_event(tmp->sector, &tmp->vertices);
	free(tmp);
	return (false);
}

bool		delete_sector_event(t_env *env, t_sector *sector)
{
	t_rec_del_sector_event	*tmp;

	if (!(tmp = (t_rec_del_sector_event *)ft_memalloc(sizeof(
		t_rec_del_sector_event))))
	{
		ft_printf("Could not record event.");
		return (false);
	}
	if (!(tmp->sector = sector_clone(sector, &tmp->vertices)))
		return (delete_event(tmp));
	tmp->func.redo = &redo_sector_deletion;
	tmp->func.undo = &undo_sector_deletion;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_DEL_SECTOR, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
