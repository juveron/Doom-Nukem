/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_menu_p3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:12:05 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 16:15:05 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "texture_menu_internal.h"

bool		change_u_texture_scale(void *text, void *param)
{
	t_gui_material_preview	*mat_prev;
	char					limit[100];

	mat_prev = param;
	mat_prev->material->uv_scale.x = ft_atof(text);
	if (mat_prev->material->uv_scale.x == 0)
		mat_prev->material->uv_scale.x = 1;
	if (mat_prev->material->uv_scale.x < 0.1
		|| mat_prev->material->uv_scale.x > 10)
	{
		mat_prev->material->uv_scale.x = clampf(mat_prev->material->uv_scale.x,
			0.1, 10);
		ft_snprintf(limit, sizeof(limit), "%f", mat_prev->material->uv_scale.x);
		if (!textfield_change_value(mat_prev->env->gui.material_menu->
			texture_scale_u_textfield, limit))
			return (false);
	}
	mat_prev->need_redraw = true;
	mat_prev->component.need_redraw = true;
	return (true);
}

bool		change_texture_rotation(void *text, void *param)
{
	t_gui_material_preview	*mat_prev;
	t_vec2f					angle;
	char					limit[100];

	mat_prev = param;
	mat_prev->material->angle = ft_atof(text);
	if (mat_prev->material->angle < 0 || mat_prev->material->angle > 360)
	{
		mat_prev->material->angle = clampf(mat_prev->material->angle, 0,
			360);
		ft_snprintf(limit, sizeof(limit), "%f", mat_prev->material->angle);
		if (!textfield_change_value(mat_prev->env->gui.material_menu->
			texture_rotation_textfield, limit))
			return (false);
	}
	angle = vec2f_from_angle(radian(mat_prev->material->angle));
	mat_prev->material->step.x = angle.x;
	mat_prev->material->step.y = angle.y;
	mat_prev->need_redraw = true;
	mat_prev->component.need_redraw = true;
	return (true);
}

bool		init_texture_menu(t_material_menu *texture_menu,
		t_material *material)
{
	char	buff[256];

	texture_menu->material = material;
	material_preview_change_material(texture_menu->material_preview, material);
	ft_snprintf(buff, sizeof(buff), "%06x", material->diffuse_color);
	if (!textfield_change_value(texture_menu->diffuse_color_textfield, buff)
		|| !ft_snprintf(buff, sizeof(buff), "%f", material->uv_pos.x)
		|| !textfield_change_value(texture_menu->texture_pos_u_textfield, buff)
		|| !ft_snprintf(buff, sizeof(buff), "%f", material->uv_pos.y)
		|| !textfield_change_value(texture_menu->texture_pos_v_textfield, buff)
		|| !ft_snprintf(buff, sizeof(buff), "%f", material->uv_scale.x)
		|| !textfield_change_value(texture_menu->texture_scale_u_textfield,
			buff)
		|| !ft_snprintf(buff, sizeof(buff), "%f", material->uv_scale.y)
		|| !textfield_change_value(texture_menu->texture_scale_v_textfield,
			buff)
		|| !ft_snprintf(buff, sizeof(buff), "%f", material->angle)
		|| !textfield_change_value(texture_menu->texture_rotation_textfield,
			buff)
		|| !init_texture_selection(texture_menu, material))
		return (false);
	return (true);
}

static bool	destroy_texture_menu_p2(t_material_menu **texture_menu, int ret)
{
	ret += !destroy_material_preview(&(*texture_menu)->material_preview);
	ret += !destroy_container(&(*texture_menu)->container);
	free((*texture_menu));
	*texture_menu = NULL;
	return (ret == 0);
}

bool		destroy_texture_menu(t_material_menu **texture_menu)
{
	int	ret;

	ret = 0;
	if (!(*texture_menu))
		return (true);
	ret += !destroy_button(&(*texture_menu)->copy_button);
	ret += !destroy_button(&(*texture_menu)->past_button);
	ret += !destroy_textfield(&(*texture_menu)->texture_rotation_textfield);
	ret += !destroy_label(&(*texture_menu)->texture_rotation_label);
	ret += !destroy_textfield(&(*texture_menu)->texture_scale_v_textfield);
	ret += !destroy_label(&(*texture_menu)->texture_scale_v_label);
	ret += !destroy_textfield(&(*texture_menu)->texture_scale_u_textfield);
	ret += !destroy_label(&(*texture_menu)->texture_scale_u_label);
	ret += !destroy_label(&(*texture_menu)->texture_scale_label);
	ret += !destroy_textfield(&(*texture_menu)->texture_pos_v_textfield);
	ret += !destroy_label(&(*texture_menu)->texture_pos_v_label);
	ret += !destroy_textfield(&(*texture_menu)->texture_pos_u_textfield);
	ret += !destroy_label(&(*texture_menu)->texture_pos_u_label);
	ret += !destroy_label(&(*texture_menu)->texture_pos_label);
	ret += !destroy_button(&(*texture_menu)->diffuse_texture_button);
	ret += !destroy_label(&(*texture_menu)->diffuse_texture_label);
	ret += !destroy_textfield(&(*texture_menu)->diffuse_color_textfield);
	ret += !destroy_label(&(*texture_menu)->diffuse_color_label);
	ret += !destroy_label(&(*texture_menu)->material_label);
	return (destroy_texture_menu_p2(texture_menu, ret));
}
