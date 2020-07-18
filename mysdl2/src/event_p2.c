/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:30:29 by killian           #+#    #+#             */
/*   Updated: 2020/05/31 15:37:58 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

static void	window_event_p3(SDL_Event *event, t_event *handle_event,
	t_window *win)
{
	if (event->window.event == SDL_WINDOWEVENT_MOVED)
	{
		win->pos.x = event->window.data1;
		win->pos.y = event->window.data2;
		handle_event->event_type |= 1 << event_moved;
	}
	else if (event->window.event == SDL_WINDOWEVENT_SHOWN)
		handle_event->event_type |= 1 << event_exposed;
}

static void	window_event_p2(SDL_Event *event, t_event *handle_event,
	t_window *win)
{
	if (event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
	{
		win->is_focus = true;
		handle_event->event_type |= 1 << event_gained_focus;
	}
	else if (event->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
	{
		win->is_focus = false;
		handle_event->event_type |= 1 << event_lost_focus;
	}
	else if (event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		win->surface = SDL_GetWindowSurface(win->handle);
		win->size.x = event->window.data1;
		win->size.y = event->window.data2;
		handle_event->event_type |= 1 << event_resized;
	}
	else if (event->window.event == SDL_WINDOWEVENT_MAXIMIZED)
		handle_event->event_type |= 1 << event_resized;
	else
		window_event_p3(event, handle_event, win);
}

void		window_event(SDL_Event *event, t_event *handle_event)
{
	t_window	*win;

	if (!(win = get_window_by_id(event->window.windowID)))
		return ;
	if (event->window.event == SDL_WINDOWEVENT_CLOSE)
	{
		win->is_close = true;
		handle_event->event_type |= 1 << event_quit;
	}
	else if (event->window.event == SDL_WINDOWEVENT_ENTER)
	{
		win->is_over = true;
		handle_event->event_type |= 1 << event_mouse_entered;
	}
	else if (event->window.event == SDL_WINDOWEVENT_LEAVE)
	{
		win->is_over = false;
		handle_event->event_type |= 1 << event_mouse_left;
	}
	else
		window_event_p2(event, handle_event, win);
}

void		update_event(void)
{
	t_context		*context;

	context = get_context();
	context->handle_event.event_type = 0;
	context->handle_event.mouse_move.delta_pos = vec2i(0, 0);
	context->handle_event.mouse_wheel.delta = 0;
	context->handle_event.textinput.text[0] = '\0';
	ft_memdel((void **)&context->handle_event.drop.file_name);
	ft_memcpy(context->handle_event.key.last_key, context->handle_event.key.key,
		sizeof(context->handle_event.key.key));
	ft_memcpy(context->handle_event.mouse_button.last_button,
		context->handle_event.mouse_button.button,
			sizeof(context->handle_event.mouse_button.button));
	while (SDL_PollEvent(&context->event))
		handle_event(&context->event);
	SDL_GetGlobalMouseState(&context->handle_event.mouse_move.global_pos.x,
		&context->handle_event.mouse_move.global_pos.y);
}
