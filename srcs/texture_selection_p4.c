/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_selection_p4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 19:49:31 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 19:49:32 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_selection_internal.h"

void			scroll_texture(t_vec2i *mouse_pos,
		t_gui_texture_selection *selection)
{
	int		wheel;
	t_vec2i	pos;
	float	tmp;

	wheel = -get_mouse_wheel();
	pos = get_component_pos((t_component *)selection);
	if (selection->env->texture_array->total
		&& wheel && is_in_box(*mouse_pos,
		&((SDL_Rect){pos.x, pos.y,
		selection->component.rect.w, selection->component.rect.h})))
	{
		if (selection->start + wheel * 5 <= 0)
			selection->start = 0;
		else
		{
			tmp = ceilf((float)(selection->env->texture_array->total
					- selection->start - wheel * 5 - 1) / 5);
			if (tmp < 5)
				selection->start = ceilf((float)((selection->env->
						texture_array->total + 1) - 25) / 5) * 5;
			else
				selection->start += wheel * 5;
		}
		selection->component.need_redraw = true;
	}
}
