/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:23:48 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 23:14:08 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool				draw_custom_win_func(void *param)
{
	t_gui_custom_window	*custom_window;

	custom_window = param;
	draw_rectangle((SDL_Rect){0, 0, custom_window->component.rect.w,
		custom_window->component.rect.h}, 0x777777FF,
		custom_window->component.surface);
	draw_elipse((SDL_Rect){custom_window->component.rect.w - 12, 7, 5, 5},
		0xFF0000FF, custom_window->component.surface);
	return (true);
}

static void			move_dragged_window(t_gui_custom_window *win,
	t_vec2i *mouse_pos, t_vec2i *pos)
{
	if (get_button_down(SDL_BUTTON_LEFT, NULL))
	{
		if (is_in_box(*mouse_pos, &(SDL_Rect){pos->x, pos->y,
			win->component.rect.w, 15}))
		{
			win->is_dragged = true;
			win->drag_offset.x = mouse_pos->x - win->component.rect.x;
			win->drag_offset.y = mouse_pos->y - win->component.rect.y;
		}
	}
	else if (get_button(SDL_BUTTON_LEFT, NULL))
	{
		if (win->is_dragged
			&& (win->component.rect.x != mouse_pos->x - win->drag_offset.x
			|| win->component.rect.y != mouse_pos->y - win->drag_offset.y))
		{
			win->component.rect.x = mouse_pos->x - win->drag_offset.x;
			win->component.rect.y = mouse_pos->y - win->drag_offset.y;
			win->component.parent->need_redraw = true;
			trigger_gui_custom_event(win->on_window_move, win);
		}
	}
	else
		win->is_dragged = false;
}

bool				update_custom_win_func(void *param)
{
	t_gui_custom_window	*custom_window;
	t_vec2i				pos;
	t_vec2i				mouse_pos;

	custom_window = param;
	mouse_pos = get_mouse_position();
	pos = get_component_pos((t_component *)custom_window);
	if (get_button_down(SDL_BUTTON_LEFT, NULL) && is_in_box(mouse_pos,
		&(SDL_Rect){pos.x + custom_window->component.rect.w - 17.5,
		pos.y + 2.5, 10, 10}))
	{
		custom_window->is_over = false;
		custom_window->component.is_visible = false;
		custom_window->component.parent->need_redraw = true;
		trigger_gui_custom_event(custom_window->on_window_close, custom_window);
		return (true);
	}
	else if (custom_window->is_draggable)
		move_dragged_window(custom_window, &mouse_pos, &pos);
	custom_window->is_over = false;
	if (is_in_box(mouse_pos, &(SDL_Rect){pos.x, pos.y,
		custom_window->component.rect.w,
		custom_window->component.rect.h}))
		custom_window->is_over = true;
	return (true);
}

t_gui_custom_window	*create_custom_window(const SDL_Rect rect,
	const t_color color)
{
	t_gui_custom_window	*window;

	if (!(window = ft_memalloc(sizeof(t_gui_custom_window))))
		return (NULL);
	if (!init_component(&window->component, &(SDL_Rect){rect.x, rect.y,
			rect.w + 10, rect.h + 20}, true, color)
		|| !(window->surface = SDL_CreateRGBSurfaceWithFormat(0,
			window->component.rect.w, window->component.rect.h, 32,
			SDL_PIXELFORMAT_RGBA8888))
		|| !(window->container = create_container((SDL_Rect){5, 15, rect.w,
			rect.h}, true, color))
		|| !(window->on_window_move = create_event_handler(CUSTOM_EVENT_TYPE))
		|| !(window->on_window_close = create_event_handler(CUSTOM_EVENT_TYPE)))
	{
		destroy_custom_window(&window);
		return (NULL);
	}
	window->component.elem_type = GUI_ELEM_CUSTOM_WINDOW;
	window->component.draw = &draw_custom_win_func;
	window->component.update = &update_custom_win_func;
	window->container->component.parent = &window->component;
	return (window);
}
