/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 22:26:04 by killian           #+#    #+#             */
/*   Updated: 2020/01/22 09:08:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
** Get the current mouse position.
**
** \return  current mouse position
*/

t_vec2i	get_mouse_position(void)
{
	return (get_context()->handle_event.mouse_move.pos);
}

/*
** Get the current mouse position delata.
**
** \return  current mouse position delta
*/

t_vec2i	get_mouse_position_delta(void)
{
	return (get_context()->handle_event.mouse_move.delta_pos);
}

/*
** Get the state of a key.
**
** \param   scancode  Enum of SDL_SCANCODE_*
**
** \return  1 if key is down , else 0 if key is up
*/

bool	get_key(SDL_Scancode scancode)
{
	return (get_context()->handle_event.key.key[scancode]);
}

/*
** Get the state down of a key
**
** \param   scancode  Enum of SDL_SCANCODE_*
**
** \return  1 if key is down on this update and up on last update, else 0
*/

bool	get_key_down(SDL_Scancode scancode)
{
	t_context	*context;

	context = get_context();
	return (context->handle_event.key.key[scancode]
		&& !context->handle_event.key.last_key[scancode]);
}

/*
** Get the state up of a key.
**
** \param   scancode  Enum of SDL_SCANCODE_*
**
** \return  1 if key is up on this update and down on last update, else 0
*/

bool	get_key_up(SDL_Scancode scancode)
{
	t_context	*context;

	context = get_context();
	return (!context->handle_event.key.key[scancode]
		&& context->handle_event.key.last_key[scancode]);
}
