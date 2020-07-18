/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 05:31:13 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/11 18:58:53 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool			draw_button_func(void *param)
{
	t_gui_button	*button;

	button = param;
	if (!button->image)
		if (!draw_component((t_component *)button->label))
			return (false);
	if (button->image)
		SDL_BlitSurface(button->image, NULL,
			button->component.surface, &(SDL_Rect){button->component.rect.w
			/ 2 - button->image->w / 2, button->component.rect.h / 2
			- button->image->h / 2, 0, 0});
	else
	{
		SDL_BlitSurface(button->label->component.surface, NULL,
				button->component.surface, &button->label->component.rect);
	}
	return (true);
}

static void		update_button_func_p2(t_gui_button *button)
{
	if (button->is_over == true)
	{
		button->is_over = false;
		trigger_gui_default_event(button->on_leave);
	}
}

bool			update_button_func(void *param)
{
	t_gui_button	*button;
	t_vec2i			pos;
	t_vec2i			mouse_pos;

	button = param;
	mouse_pos = get_mouse_position();
	pos = get_component_pos((t_component *)button);
	if (is_in_box(mouse_pos, &(SDL_Rect){pos.x, pos.y,
		button->component.rect.w, button->component.rect.h}))
	{
		if (button->is_over == false)
		{
			button->is_over = true;
			trigger_gui_default_event(button->on_enter);
		}
		if (get_button_down(SDL_BUTTON_LEFT, NULL))
			trigger_gui_default_event(button->on_click);
	}
	else
		update_button_func_p2(button);
	return (true);
}

t_gui_button	*create_button(const SDL_Rect rect, const t_color color,
	TTF_Font *font)
{
	t_gui_button	*button;

	if (!(button = ft_memalloc(sizeof(t_gui_button))))
		return (NULL);
	if (!init_component(&button->component, &rect, true, color)
	|| !(button->label = create_label((t_vec2i){0, 0}, 0xFFFFFFFF, font, 0x0))
		|| !(button->on_click = create_event_handler(DEFAULT_EVENT_TYPE))
		|| !(button->on_enter = create_event_handler(DEFAULT_EVENT_TYPE))
		|| !(button->on_leave = create_event_handler(DEFAULT_EVENT_TYPE)))
	{
		destroy_button(&button);
		return (NULL);
	}
	button->component.elem_type = GUI_ELEM_BUTTON;
	button->component.draw = &draw_button_func;
	button->component.update = &update_button_func;
	button->label->component.rect.x = button->component.rect.w / 2
		- button->label->component.rect.w / 2;
	button->label->component.rect.y = button->component.rect.h / 2
		- button->label->component.rect.h / 2;
	button->label->component.parent = &button->component;
	return (button);
}

bool			destroy_button(t_gui_button **button)
{
	int	ret;

	ret = 0;
	if (*button == NULL)
		return (true);
	ret += !component_remove_from_parent(*button);
	ret += !destroy_label(&(*button)->label);
	destroy_event_handler((*button)->on_click);
	destroy_event_handler((*button)->on_enter);
	destroy_event_handler((*button)->on_leave);
	destroy_component(&(*button)->component);
	free(*button);
	*button = NULL;
	return (ret == 0);
}
