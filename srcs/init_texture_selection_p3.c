/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_selection_p3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:48:52 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 17:48:53 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	init_texture_selection_p2(t_material_menu *menu,
		t_gui_texture_selection *selec, t_material *material)
{
	t_texture				*texture;
	size_t					i;

	i = 0;
	texture = NULL;
	while (i < menu->env->texture_array->total)
	{
		texture = *(t_texture **)map_get_index(menu->env->texture_array, i);
		if (texture->id == material->diffuse_texture->id)
			break ;
		++i;
	}
	selec->section_pos = i + 1;
	selec->current_texture = texture;
	selec->component.need_redraw = true;
	return (trigger_custom_event(selec->on_selection_change, selec));
}

bool		init_texture_selection(t_material_menu *menu, t_material *material)
{
	t_gui_texture_selection	*selec;

	selec = menu->env->gui.texture_menu->texture_selection;
	if (material->diffuse_texture)
		return (init_texture_selection_p2(menu, selec, material));
	else
	{
		selec->section_pos = 0;
		selec->current_texture = NULL;
		selec->component.need_redraw = true;
		return (trigger_custom_event(selec->on_selection_change, selec));
	}
}

static bool	update_texture_info_p2(char *buff,
		t_selec_texure_menu *texture_menu, t_gui_texture_selection *selection)
{
	ft_snprintf(buff, 47, "id: %lu", selection->
			current_texture->id);
	if (!label_change_name(texture_menu->texture_id_info, buff))
		return (false);
	ft_snprintf(buff, 47, "name: %s", selection->
			current_texture->name);
	if (!label_change_name(texture_menu->texture_name_info, buff))
		return (false);
	return (true);
}

bool		update_texture_info(void *param, void *data)
{
	t_gui_texture_selection *selection;
	t_selec_texure_menu		*texture_menu;
	char					buff[47];

	selection = param;
	texture_menu = data;
	if (selection->current_texture == NULL)
	{
		ft_snprintf(buff, sizeof(buff), "id: null");
		if (!label_change_name(texture_menu->texture_id_info, buff))
			return (false);
		ft_snprintf(buff, sizeof(buff), "name: null");
		if (!label_change_name(texture_menu->texture_name_info, buff))
			return (false);
	}
	else
		update_texture_info_p2(buff, texture_menu, selection);
	return (true);
}
