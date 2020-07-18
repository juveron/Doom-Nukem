/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_preview.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 11:12:30 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 15:52:53 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_preview_internal.h"

void					material_preview_change_material(
	t_gui_material_preview *mat_prev, t_material *mat)
{
	mat_prev->material = mat;
	mat_prev->need_redraw = true;
	mat_prev->component.need_redraw = true;
}

t_gui_material_preview	*create_material_preview(SDL_Rect rect, t_env *env)
{
	t_gui_material_preview	*mat_prev;

	if (!(mat_prev = ft_memalloc(sizeof(t_gui_material_preview))))
		return (NULL);
	if (!init_component(&mat_prev->component, &rect, false, 0)
		|| !(mat_prev->surface = SDL_CreateRGBSurfaceWithFormat(0, rect.w,
			rect.h, 32, SDL_PIXELFORMAT_RGB888)))
	{
		destroy_material_preview(&mat_prev);
		return (NULL);
	}
	mat_prev->component.elem_type = GUI_ELEM_CUSTOM;
	mat_prev->component.draw = &draw_mat_prev_func;
	mat_prev->component.update = &update_mat_prev_func;
	mat_prev->env = env;
	return (mat_prev);
}

bool					destroy_material_preview(
	t_gui_material_preview **mat_prev)
{
	int	ret;

	ret = 0;
	if (*mat_prev == NULL)
		return (true);
	ret += !component_remove_from_parent(*mat_prev);
	destroy_component(&(*mat_prev)->component);
	SDL_FreeSurface((*mat_prev)->surface);
	free(*mat_prev);
	*mat_prev = NULL;
	return (ret == 0);
}
