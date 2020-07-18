/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 10:19:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/15 21:55:26 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"
#include "game.h"
#include "inputs.h"

int		loop(t_env *env)
{
	t_context		*context;
	t_scene_manager	*scene_manager;

	context = get_context();
	scene_manager = get_scene_manager();
	while (context->run)
	{
		update_event();
		if (!scene_manager->current_scene->update(scene_manager->
			current_scene->param))
			return (false);
		if (env->main_window->is_close)
			context->run = false;
		if (!scene_manager->current_scene->draw(scene_manager->current_scene->
			param)
			|| !update_gui(env->main_window)
			|| (env->editor.history.available
			&& !update_gui(env->editor.history.window))
			|| !update_window()
			|| !update_scene_manager())
			return (false);
	}
	return (true);
}

bool	update_doom_physics(void *param, float dt)
{
	t_env	*env;
	t_vec3f	gravity;

	env = param;
	if (env->app_state != APP_GAME && env->app_state != APP_EDITOR_GAME)
		return (true);
	if (env->app_state == APP_EDITOR_GAME || env->app_state == APP_GAME)
		global_movement_ph_inputs(env, dt);
	if (env->use_gravity)
	{
		if (!check_collision(env, dt))
			return (false);
		gravity = vec3f(0, -9.81f, 0);
		update_gravity(&gravity, &env->player.physic, dt, 20);
	}
	else
		env->player.transform->position = vec3f_add(env->player.transform->
				position, env->player.new_pos);
	env->player.new_pos = vec3f(0, 0, 0);
	return (true);
}

int		exit_app(t_env *env, int ret)
{
	free(env->camera.depth_buffer);
	free_all(env);
	free_env(env);
	return (ret);
}

int		app_run_p2(t_env *env)
{
	env->player.transform = &env->camera.transform;
	ft_bzero(&env->player.physic, sizeof(t_physics_component));
	init_ph_context(&env->ph_context);
	ph_add_update_func(&env->ph_context, update_doom_physics, env);
	if (!loop(env))
	{
		unload_current_scene();
		update_scene_manager();
		return (exit_app(env, 0));
	}
	return (1);
}

int		app_run(char **av)
{
	t_env		*env;

	env = NULL;
	if (!load_env_and_map(&env, av))
		return (1);
	set_framerate(60);
	if (!init_3d(env)
		|| !init_levels_manager(env, &env->levels_manager)
		|| !load_all_scene(env) || !get_scene_manager())
		return (exit_app(env, 0));
	load_scene(env->scenes.main_menu);
	if (!update_scene_manager())
		return (exit_app(env, 0));
	if (!app_run_p2(env))
		return (0);
	unload_current_scene();
	if (!update_scene_manager())
		return (exit_app(env, 0));
	return (exit_app(env, 1));
}
