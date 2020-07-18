/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_button_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:10:12 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 18:10:13 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	input_button_change_name(t_gui_input_button *input_button,
	const char *name)
{
	if (label_change_name(input_button->label, name) == false)
		return (false);
	input_button->label->component.rect.x = input_button->component.rect.w / 2
		- input_button->label->component.rect.w / 2;
	input_button->label->component.rect.y = input_button->component.rect.h / 2
		- input_button->label->component.rect.h / 2;
	input_button->component.need_redraw = true;
	return (true);
}

void	input_button_add_image(t_gui_input_button *input_button,
	SDL_Surface *surface)
{
	input_button->image = surface;
	input_button->component.need_redraw = true;
}

void	input_button_remove_image(t_gui_input_button *input_button)
{
	input_button->image = NULL;
	input_button->component.need_redraw = true;
}
