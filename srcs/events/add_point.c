/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:24:17 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 17:29:07 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"

static bool	undo_point_return(t_env *env)
{
	if (!change_selection_mode(env, EDITOR_SELECT_LINE))
		return (false);
	send_notify("Removed last point.", 0xFFFFFF, env);
	return (true);
}

static bool	undo_point(t_env *env, void *param)
{
	(void)param;
	if (env->editor.tmp_vertices.total == 0)
		return (true);
	else if (env->editor.tmp_vertices.total == 1)
	{
		vector_free(&env->editor.tmp_sector->walls);
		free(env->editor.tmp_sector);
		free_point(*(t_point **)vector_get(&env->editor.tmp_vertices, 0));
		vector_free(&env->editor.tmp_vertices);
		--env->editor.unique_id_sectors;
		env->editor.state.global_state = EDITOR_IDLE;
	}
	else
	{
		vector_delete(&env->editor.tmp_sector->walls,
			env->editor.tmp_sector->walls.total - 1);
		free_point(*(t_point **)vector_get(&env->editor.tmp_vertices, env->
			editor.tmp_vertices.total - 1));
		vector_delete(&env->editor.tmp_vertices,
			env->editor.tmp_vertices.total - 1);
	}
	--env->editor.unique_id_vertices;
	return (undo_point_return(env));
}

static bool	delete_event(void *param)
{
	t_rec_add_point_event	*tmp_struct;

	tmp_struct = param;
	point_free(tmp_struct->position);
	free(tmp_struct);
	return (false);
}

bool		add_point_event(t_env *env, t_point *position)
{
	t_rec_add_point_event	*tmp_struct;

	if (!(tmp_struct = (t_rec_add_point_event *)malloc(sizeof(
		t_rec_add_point_event))))
	{
		ft_printf("Could not record event.");
		return (false);
	}
	if (!(tmp_struct->position = point_clone(position)))
		return (delete_event(tmp_struct));
	tmp_struct->func.redo = &redo_point;
	tmp_struct->func.undo = &undo_point;
	tmp_struct->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_ADD_POINT, (void *)tmp_struct))
		return (delete_event(tmp_struct));
	return (true);
}
