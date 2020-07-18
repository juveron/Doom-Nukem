/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_menu_p4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:12:59 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 16:15:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "texture_menu_internal.h"

bool	change_v_texture_scale(void *text, void *param)
{
	t_gui_material_preview	*mat_prev;
	char					limit[100];

	mat_prev = param;
	mat_prev->material->uv_scale.y = ft_atof(text);
	if (mat_prev->material->uv_scale.y == 0)
		mat_prev->material->uv_scale.y = 1;
	if (mat_prev->material->uv_scale.y < 0.1
		|| mat_prev->material->uv_scale.y > 10)
	{
		mat_prev->material->uv_scale.y = clampf(mat_prev->material->uv_scale.y,
			0.1, 10);
		ft_snprintf(limit, sizeof(limit), "%f", mat_prev->material->uv_scale.y);
		if (!textfield_change_value(mat_prev->env->gui.material_menu->
			texture_scale_v_textfield, limit))
			return (false);
	}
	mat_prev->need_redraw = true;
	mat_prev->component.need_redraw = true;
	return (true);
}

bool	change_diffuse_color(void *text, void *param)
{
	t_gui_material_preview	*mat_prev;

	mat_prev = param;
	mat_prev->material->diffuse_color = ft_atoi_hex(text);
	mat_prev->need_redraw = true;
	mat_prev->component.need_redraw = true;
	mat_prev->component.need_redraw = true;
	return (true);
}

bool	change_u_texture_pos(void *text, void *param)
{
	t_gui_material_preview	*mat_prev;
	char					limit[100];

	mat_prev = param;
	mat_prev->material->uv_pos.x = ft_atof(text);
	if (mat_prev->material->uv_pos.x < -10 || mat_prev->material->uv_pos.x > 10)
	{
		mat_prev->material->uv_pos.x = clampf(mat_prev->material->uv_pos.x, -10,
			10);
		ft_snprintf(limit, sizeof(limit), "%f", mat_prev->material->uv_pos.x);
		if (!textfield_change_value(mat_prev->env->gui.material_menu->
			texture_pos_u_textfield, limit))
			return (false);
	}
	mat_prev->need_redraw = true;
	mat_prev->component.need_redraw = true;
	return (true);
}

bool	change_v_texture_pos(void *text, void *param)
{
	t_gui_material_preview	*mat_prev;
	char					limit[100];

	mat_prev = param;
	mat_prev->material->uv_pos.y = ft_atof(text);
	if (mat_prev->material->uv_pos.y < -10 || mat_prev->material->uv_pos.y > 10)
	{
		mat_prev->material->uv_pos.y = clampf(mat_prev->material->uv_pos.y, -10,
			10);
		ft_snprintf(limit, sizeof(limit), "%f", mat_prev->material->uv_pos.y);
		if (!textfield_change_value(mat_prev->env->gui.material_menu->
			texture_pos_v_textfield, limit))
			return (false);
	}
	mat_prev->component.need_redraw = true;
	mat_prev->need_redraw = true;
	return (true);
}
