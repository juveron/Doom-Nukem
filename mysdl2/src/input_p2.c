/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:47:24 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:08:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
** Get the state of a button and his position.
**
** \param   sdl_button  Define of SDL_BUTTON_*
** \param   pos  NULL do nothing, else get position of the last state
**
** \return  1 if button is down, 0 if button is up
*/

bool	get_button(int sdl_button, t_vec2i *pos)
{
	t_context	*context;

	context = get_context();
	if (pos)
		*pos = context->handle_event.mouse_button.button[sdl_button].pos;
	return (context->handle_event.mouse_button.button[sdl_button].is_pressed);
}

/*
** Get the state down of a button and his position.
**
** \param   sdl_button  Define of SDL_BUTTON_*
** \param   pos  NULL do nothing, else get position of the last state if state
** down is 1
**
** \return  1 if button is down on this update and up on last update, else 0
*/

bool	get_button_down(int sdl_button, t_vec2i *pos)
{
	t_context	*context;
	bool		is_down;

	context = get_context();
	is_down = context->handle_event.mouse_button.button[sdl_button].is_pressed
		&& !context->handle_event.mouse_button.last_button[sdl_button].
			is_pressed;
	if (pos && is_down)
		*pos = context->handle_event.mouse_button.button[sdl_button].pos;
	return (is_down);
}

/*
** Get the state up of a button and his position.
**
** \param   sdl_button  Define of SDL_BUTTON_*
** \param   pos  NULL do nothing, else get position of the last state if state
** up is 1
**
** \return  1 if button is up on this update and down on last update, else 0
*/

bool	get_button_up(int sdl_button, t_vec2i *pos)
{
	t_context	*context;
	bool		is_up;

	context = get_context();
	is_up = !context->handle_event.mouse_button.button[sdl_button].is_pressed
		&& context->handle_event.mouse_button.last_button[sdl_button].
			is_pressed;
	if (pos && is_up)
		*pos = context->handle_event.mouse_button.button[sdl_button].pos;
	return (is_up);
}

/*
** Get mouse wheel delta.
**
** \return  mouse wheel delta
*/

t_s32	get_mouse_wheel(void)
{
	return (get_context()->handle_event.mouse_wheel.delta);
}

/*
** Get the number of click on a button.
**
** \param   sdl_button  Define of SDL_BUTTON_*
**
** \return  number of click
*/

t_u8	get_click(int sdl_button)
{
	return (get_context()->handle_event.mouse_button.button[sdl_button].clicks);
}
