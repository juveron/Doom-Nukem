/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_selection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 09:19:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/19 16:18:58 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"

bool				update_wall_menu(void *param, void *data)
{
	t_gui_material_preview	*prev;
	t_gui_texture_selection	*selec;

	selec = param;
	prev = data;
	if (!mtl_remove_diffuse_texture(prev->material))
		return (false);
	if (!mtl_add_diffuse_texture(prev->material, selec->current_texture))
		return (false);
	prev->need_redraw = true;
	prev->component.need_redraw = true;
	return (true);
}

bool				delete_texture(void *param)
{
	t_gui_texture_selection	*selec;
	bool					err;

	selec = param;
	if (selec->current_texture)
	{
		err = map_delete(selec->env->texture_array, selec->current_texture->id);
		destroy_texture(&selec->current_texture);
		selec->current_texture = NULL;
		selec->section_pos = 0;
		if (err == false)
			return (false);
		trigger_gui_custom_event(selec->on_selection_change, selec);
		selec->component.need_redraw = true;
	}
	return (true);
}

bool				create_selec_texture_menu_p3(t_env *env,
		t_selec_texure_menu *texture_menu)
{
	if (!(texture_menu->delete_button = create_button((SDL_Rect){320, 160,
			170, 30}, 0x777777FF, env->fonts.deja_vu_sans_momo_16))
		|| !button_change_name(texture_menu->delete_button, "Delete texture")
		|| !add_default_action(texture_menu->delete_button->on_click,
				&(t_default_event){delete_texture,
				texture_menu->texture_selection})
		|| !container_add(texture_menu->container, texture_menu->delete_button)
		|| !container_add(texture_menu->window->container,
				texture_menu->container))
		return (false);
	return (true);
}

bool				create_selec_texture_menu_p2(t_env *env,
	t_selec_texure_menu *texture_menu)
{
	if (!(texture_menu->texture_selection = create_texture_selection(
			(SDL_Rect){10, 200, 480, 490}, env))
		|| !add_custom_action(texture_menu->texture_selection->
			on_selection_change, &(t_custom_event){&update_wall_menu,
			env->gui.material_menu->material_preview})
		|| !add_custom_action(texture_menu->texture_selection->
			on_selection_change, &(t_custom_event){&update_texture_info,
			texture_menu})
		|| !container_add(texture_menu->container,
			texture_menu->texture_selection)
		|| !(texture_menu->texture_id_info = create_label((t_vec2i){20, 20},
			0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x777777FF))
		|| !label_change_name(texture_menu->texture_id_info, "id: null")
		|| !container_add(texture_menu->container,
			texture_menu->texture_id_info)
		|| !(texture_menu->texture_name_info = create_label((t_vec2i){20, 50},
			0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x777777FF))
		|| !label_change_name(texture_menu->texture_name_info, "name: null")
		|| !container_add(texture_menu->container,
			texture_menu->texture_name_info)
		|| !create_selec_texture_menu_p3(env, texture_menu))
		return (false);
	return (true);
}

t_selec_texure_menu	*create_selec_texture_menu(t_env *env)
{
	t_selec_texure_menu	*texture_menu;

	if (!(texture_menu = ft_memalloc(sizeof(t_selec_texure_menu)))
		|| !(texture_menu->window = create_custom_window((SDL_Rect)
			{env->gui.window->component.rect.x - 520,
			env->gui.window->component.rect.y, 500, 700}, 0x333333FF))
		|| !add_default_action(env->gui.material_menu->diffuse_texture_button->
			on_click, &(t_default_event){&show_texture_window, env})
		|| !add_custom_action(env->gui.window->on_window_move,
			&(t_custom_event){&move_texture_window, texture_menu->window})
		|| !add_custom_action(env->gui.window->on_window_close,
			&(t_custom_event){&close_texture_window, texture_menu->window})
		|| !container_add(env->main_window->main_container,
			texture_menu->window)
		|| !(texture_menu->container = create_container(rect(0, 0, 500, 700),
				false, 0x0))
		|| !create_selec_texture_menu_p2(env, texture_menu))
	{
		destroy_select_texture_menu(texture_menu);
		return (NULL);
	}
	return (texture_menu);
}
