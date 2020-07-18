/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_options_p3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 19:15:52 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 16:29:36 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	disable_skybox(void *text, void *param)
{
	t_env	*env;
	bool	*checked;

	env = param;
	checked = text;
	env->sky_enable = *checked;
	return (true);
}

bool	enable_debug_triangles(void *text, void *param)
{
	bool	*checked;

	(void)param;
	checked = text;
	get_context()->context_3d->debug_clip = *checked;
	return (true);
}

bool	enable_fps(void *text, void *param)
{
	t_env	*env;
	bool	*checked;

	env = param;
	checked = text;
	if (*checked)
		enable_fps_counter(env->main_window);
	else
		disable_fps_counter(env->main_window);
	return (true);
}

bool	enable_animation(void *text, void *param)
{
	t_env	*env;
	bool	*checked;

	env = param;
	checked = text;
	env->game_over.active = *checked;
	return (true);
}

void	verify_other_check_boxes(t_env *env, t_other_options *other)
{
	t_context	*context;

	context = get_context();
	if (env->sky_enable != other->skybox_check_box->checked)
		check_box_enable(other->skybox_check_box, env->sky_enable);
	if (context->context_3d->debug_clip != other->debug_triangles_check_box->
		checked)
	{
		check_box_enable(other->debug_triangles_check_box,
			context->context_3d->debug_clip);
	}
	if ((!env->main_window->fps_counter && other->fps_check_box->checked)
		|| (env->main_window->fps_counter && !other->fps_check_box->checked))
		check_box_enable(other->fps_check_box, !other->fps_check_box->checked);
	if (env->game_over.active != other->game_over_animation_check_box->checked)
	{
		check_box_enable(other->game_over_animation_check_box,
			env->game_over.active);
	}
}
