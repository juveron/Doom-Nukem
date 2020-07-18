/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:10:52 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 15:37:50 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "event_p2.h"

static void	mouse_button_event(SDL_Event *event, t_event *handle_event,
	bool is_down)
{
	handle_event->mouse_button.button[event->button.button].
	is_pressed = is_down;
	handle_event->mouse_button.button[event->button.button].
	pos.x = event->button.x;
	handle_event->mouse_button.button[event->button.button].
	pos.y = event->button.y;
	handle_event->mouse_button.button[event->button.button].
	clicks = event->button.clicks;
	if (is_down)
		handle_event->event_type |= 1 << event_mouse_button_pressed;
	else
		handle_event->event_type |= 1 << event_mouse_button_released;
}

static void	key_event(SDL_Event *event, t_event *handle_event,
	bool is_down)
{
	handle_event->key.key[event->key.keysym.scancode] = is_down;
	if (is_down)
		handle_event->event_type |= 1 << event_key_pressed;
	else
		handle_event->event_type |= 1 << event_key_released;
}

static void	mouse_motion_event(SDL_Event *event, t_event *handle_event)
{
	handle_event->mouse_move.pos.x = event->motion.x;
	handle_event->mouse_move.pos.y = event->motion.y;
	handle_event->mouse_move.delta_pos.x = event->motion.xrel;
	handle_event->mouse_move.delta_pos.y = event->motion.yrel;
	handle_event->event_type |= 1 << event_mouse_moved;
}

static void	handle_event_p2(SDL_Event *event, t_event *handle_event)
{
	if (event->type == SDL_TEXTINPUT)
		ft_strlcat(handle_event->textinput.text, event->text.text,
			sizeof(handle_event->textinput.text));
	else if (event->type == SDL_DROPFILE)
	{
		if (event->drop.file != NULL)
			handle_event->drop.file_name = ft_strdup(event->drop.file);
		SDL_free(event->drop.file);
	}
}

void		handle_event(SDL_Event *event)
{
	t_event		*handle_event;
	t_context	*context;

	context = get_context();
	handle_event = &context->handle_event;
	if (event->type == SDL_WINDOWEVENT)
		window_event(event, handle_event);
	else if (event->type == SDL_MOUSEMOTION)
		mouse_motion_event(event, handle_event);
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		mouse_button_event(event, handle_event, true);
	else if (event->type == SDL_MOUSEBUTTONUP)
		mouse_button_event(event, handle_event, false);
	else if (event->type == SDL_MOUSEWHEEL)
	{
		handle_event->mouse_wheel.delta = event->wheel.y;
		handle_event->event_type = event_mouse_wheel_moved;
	}
	else if (event->type == SDL_KEYDOWN)
		key_event(event, handle_event, true);
	else if (event->type == SDL_KEYUP)
		key_event(event, handle_event, false);
	else
		handle_event_p2(event, handle_event);
}
