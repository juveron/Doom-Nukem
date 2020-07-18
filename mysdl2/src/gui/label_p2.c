/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 23:21:01 by thboura           #+#    #+#             */
/*   Updated: 2020/05/30 23:21:31 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void	label_change_color(t_gui_label *label, const t_color color)
{
	label->color = color;
	label->need_redraw = true;
	label->component.need_redraw = true;
}

bool	label_change_name(t_gui_label *label, const char *name)
{
	t_vec2i	size;

	free(label->name);
	if (!(label->name = ft_strdup(name)))
		return (false);
	TTF_SizeText(label->font, label->name, &size.x, &size.y);
	label->component.rect = (SDL_Rect){label->component.rect.x,
		label->component.rect.y, size.x, size.y};
	label->need_redraw = true;
	label->component.need_redraw = true;
	return (true);
}
