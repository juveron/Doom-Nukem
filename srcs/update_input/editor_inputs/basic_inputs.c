/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:37:42 by thboura           #+#    #+#             */
/*   Updated: 2020/06/13 16:53:33 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static void	movements_inputs(t_env *env, float dt)
{
	if (get_key(SDL_SCANCODE_LEFT))
		env->editor.offset.x += 400.f / env->editor.zoom * dt;
	if (get_key(SDL_SCANCODE_RIGHT))
		env->editor.offset.x += -400.f / env->editor.zoom * dt;
	if (get_key(SDL_SCANCODE_UP))
		env->editor.offset.y += 400.f / env->editor.zoom * dt;
	if (get_key(SDL_SCANCODE_DOWN))
		env->editor.offset.y += -400.f / env->editor.zoom * dt;
	if (get_key(SDL_SCANCODE_LEFT) || get_key(SDL_SCANCODE_RIGHT)
		|| get_key(SDL_SCANCODE_UP) || get_key(SDL_SCANCODE_DOWN))
		env->need_redraw = true;
}

void		zoom_inputs(t_env *env)
{
	if (get_mouse_wheel() != 0
		&& !(get_key(env->shortcuts.editor.mouse_wheel.move)))
		zoom(get_mouse_position(), env, 1 - 0.1f * -get_mouse_wheel());
	else if (get_mouse_wheel() != 0
		&& get_key(env->shortcuts.editor.mouse_wheel.move))
	{
		if (get_key(SDL_SCANCODE_LALT))
			env->editor.offset.y += 0.1 * get_mouse_wheel();
		else
			env->editor.offset.x += 0.1 * get_mouse_wheel();
		env->need_redraw = true;
	}
	if (get_key(env->shortcuts.editor.zoom.out) && env->editor.zoom - 5 > 1)
		zoom(get_mouse_position(), env, 0.9f);
	if (get_key(env->shortcuts.editor.zoom.in))
		zoom(get_mouse_position(), env, 1.1f);
}

static void	grid_modification_inputs(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.grid.decrease)
		&& env->editor.div / 2 >= 1)
	{
		env->need_redraw = true;
		env->editor.div /= 2;
	}
	if (get_key_down(env->shortcuts.editor.grid.increase)
		&& env->editor.div * 2 <= 8)
	{
		env->need_redraw = true;
		env->editor.div *= 2;
	}
}

void		enable_fps_input(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.fps))
	{
		if (!env->main_window->fps_counter)
			enable_fps_counter(env->main_window);
		else
			disable_fps_counter(env->main_window);
		env->need_redraw = true;
	}
}

void		basic_inputs(t_env *env, float dt)
{
	movements_inputs(env, dt);
	grid_modification_inputs(env);
	enable_fps_input(env);
}
