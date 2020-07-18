/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:02:58 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 17:39:19 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	disable_current_key_event(SDL_Scancode scancode)
{
	t_context	*context;

	context = get_context();
	context->handle_event.key.key[scancode] = false;
	context->handle_event.key.last_key[scancode] = true;
}

static void	disable_current_button_event(int button)
{
	t_context	*context;

	context = get_context();
	context->handle_event.mouse_button.button[button].is_pressed = false;
	context->handle_event.mouse_button.last_button[button].is_pressed = true;
}

int			input(void *data, SDL_Event *event)
{
	t_env			*env;

	env = (t_env *)data;
	if (env->gui.status == GUI_INPUT)
	{
		if (event->type == SDL_KEYDOWN)
		{
			if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				env->gui.input_handler.input_scancode = 0;
			else
			{
				env->gui.input_handler.input_scancode = event->key.keysym.
					scancode;
				if (!env->gui.input_handler.set_input_func(env,
					event->key.keysym.scancode))
					get_context()->run = false;
			}
			disable_current_key_event(event->key.keysym.scancode);
			env->gui.status = env->gui.input_handler.previous_state;
			destroy_input_display(env, &env->gui.input_handler.display);
		}
		else if (event->type == SDL_MOUSEBUTTONDOWN)
			disable_current_button_event(event->button.button);
	}
	return (1);
}
