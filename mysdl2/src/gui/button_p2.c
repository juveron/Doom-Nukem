/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 22:45:17 by thboura           #+#    #+#             */
/*   Updated: 2020/05/30 22:47:57 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool	check_button_is_over(t_gui_button *button)
{
	t_vec2i	pos;
	t_vec2i	mouse_pos;

	mouse_pos = get_mouse_position();
	pos = get_component_pos((t_component *)button);
	if (is_in_box(mouse_pos, &(SDL_Rect){pos.x, pos.y,
		button->component.rect.w, button->component.rect.h}))
	{
		if (button->is_over == true)
			return (true);
		else
			return (!(button->is_over = true));
	}
	else
	{
		if (button->is_over == false)
			return (true);
		else
			return ((button->is_over = false));
	}
}

bool	button_change_name(t_gui_button *button, const char *name)
{
	if (label_change_name(button->label, name) == false)
		return (false);
	button->label->component.rect.x = button->component.rect.w / 2
		- button->label->component.rect.w / 2;
	button->label->component.rect.y = button->component.rect.h / 2
		- button->label->component.rect.h / 2;
	button->component.need_redraw = true;
	return (true);
}

void	button_add_image(t_gui_button *button, SDL_Surface *surface)
{
	button->image = surface;
	button->component.need_redraw = true;
}

void	button_remove_image(t_gui_button *button)
{
	button->image = NULL;
	button->component.need_redraw = true;
}
