/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_button.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:08:25 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 18:09:23 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool				draw_input_button_func(void *param)
{
	t_gui_input_button	*input_button;

	input_button = param;
	if (!input_button->image)
		if (!draw_component((t_component *)input_button->label))
			return (false);
	draw_rectangle((SDL_Rect){0, 0, input_button->component.rect.w,
		input_button->component.rect.h}, input_button->component.background,
		input_button->component.surface);
	if (input_button->image)
		SDL_BlitSurface(input_button->image, NULL,
			input_button->component.surface, &(SDL_Rect){input_button->
			component.rect.w / 2 - input_button->image->w / 2, input_button->
			component.rect.h / 2 - input_button->image->h / 2, 0, 0});
	else
	{
		SDL_BlitSurface(input_button->label->component.surface, NULL,
			input_button->component.surface, &input_button->label->component.
			rect);
	}
	return (true);
}

bool				update_input_button_func(void *param)
{
	t_gui_input_button	*input_button;
	t_vec2i				pos;
	t_vec2i				mouse_pos;

	input_button = param;
	mouse_pos = get_mouse_position();
	pos = get_component_pos((t_component *)input_button);
	if (get_button_down(SDL_BUTTON_LEFT, NULL) && is_in_box(mouse_pos,
		&(SDL_Rect){pos.x, pos.y, input_button->component.rect.w,
		input_button->component.rect.h}))
	{
		trigger_custom_event(input_button->on_click,
			input_button->env);
	}
	return (true);
}

t_gui_input_button	*create_input_button(const SDL_Rect rect,
	const t_color color, TTF_Font *font, t_env *env)
{
	t_gui_input_button	*input_button;

	if (!(input_button = ft_memalloc(sizeof(t_gui_input_button))))
		return (NULL);
	if (!init_component(&input_button->component, &rect, true, color)
		|| !(input_button->label = create_label((t_vec2i){0, 0}, 0xFFFFFFFF,
			font, 0x0))
		|| !(input_button->on_click = create_event_handler(CUSTOM_EVENT_TYPE)))
	{
		destroy_input_button(&input_button);
		return (NULL);
	}
	input_button->component.elem_type = GUI_ELEM_CUSTOM;
	input_button->component.draw = &draw_input_button_func;
	input_button->component.update = &update_input_button_func;
	input_button->label->component.rect.x = input_button->component.rect.w / 2
		- input_button->label->component.rect.w / 2;
	input_button->label->component.rect.y = input_button->component.rect.h / 2
		- input_button->label->component.rect.h / 2;
	input_button->label->component.parent = &input_button->component;
	input_button->env = env;
	return (input_button);
}

bool				destroy_input_button(t_gui_input_button **input_button)
{
	int	ret;

	ret = 0;
	if (*input_button == NULL)
		return (true);
	ret += !destroy_label(&(*input_button)->label);
	destroy_event_handler((*input_button)->on_click);
	destroy_component(&(*input_button)->component);
	free(*input_button);
	*input_button = NULL;
	return (ret == 0);
}
