/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_menu_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:11:57 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/05 12:12:53 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "texture_menu_internal.h"

static bool	internal_texture_menu_8(t_container *container,
		t_material_menu *texture_menu, t_env *env)
{
	if (!(texture_menu->past_button = create_button(rect(180, 330 + 50, 100,
			40), 0x777777FF, env->fonts.deja_vu_sans_momo_16))
		|| !button_change_name(texture_menu->past_button, "Past")
		|| !add_default_action(texture_menu->past_button->on_click,
			&(t_default_event){&past_material, texture_menu})
		|| !container_add(container, texture_menu->past_button))
		return (false);
	texture_menu->selec_texture_menu_open = false;
	return (true);
}

static bool	internal_texture_menu_7(t_container *container,
	t_material_menu *texture_menu, t_env *env)
{
	if (!(texture_menu->texture_rotation_textfield = create_textfield(
			(SDL_Rect){170, 280 + 50, 115, 40}, 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16))
		|| !add_custom_action(texture_menu->texture_rotation_textfield->
			on_text_change, &(t_custom_event){&change_texture_rotation,
			texture_menu->material_preview})
		|| !textfield_change_limit(texture_menu->texture_rotation_textfield, 10)
		|| !textfield_change_default_text(texture_menu->
			texture_rotation_textfield, "Float")
		|| !container_add(container, texture_menu->texture_rotation_textfield)
		|| !(texture_menu->copy_button = create_button(rect(40, 330 + 50, 100,
				40), 0x777777FF, env->fonts.deja_vu_sans_momo_16))
		|| !button_change_name(texture_menu->copy_button, "Copy")
		|| !add_default_action(texture_menu->copy_button->on_click,
			&(t_default_event){&copy_material, texture_menu})
		|| !container_add(container, texture_menu->copy_button)
		|| !internal_texture_menu_8(container, texture_menu, env))
		return (false);
	return (true);
}

static bool	internal_texture_menu_6(t_container *container,
	t_material_menu *texture_menu, t_env *env)
{
	texture_menu->env = env;
	if (!(texture_menu->texture_scale_v_textfield = create_textfield(
			(SDL_Rect){185, 230 + 50, 115, 40}, 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16))
		|| !add_custom_action(texture_menu->texture_scale_v_textfield->
			on_text_change, &(t_custom_event){&change_v_texture_scale,
			texture_menu->material_preview})
		|| !textfield_change_limit(texture_menu->texture_scale_v_textfield, 10)
		|| !textfield_change_default_text(texture_menu->
			texture_scale_v_textfield, "Float")
		|| !container_add(container, texture_menu->texture_scale_v_textfield)
		|| !(texture_menu->texture_rotation_label = create_label(vec2i(70,
			290 + 50), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->texture_rotation_label, "Rotation")
		|| !container_add(container, texture_menu->texture_rotation_label))
		return (false);
	return (internal_texture_menu_7(container, texture_menu, env));
}

bool		internal_texture_menu_5(t_container *container,
	t_material_menu *texture_menu, t_env *env)
{
	if (!(texture_menu->texture_scale_u_textfield = create_textfield(
				(SDL_Rect){40, 230 + 50, 115, 40}, 0xFFFFFFFF, env->fonts.
				deja_vu_sans_momo_16))
		|| !add_custom_action(texture_menu->texture_scale_u_textfield->
			on_text_change, &(t_custom_event){&change_u_texture_scale,
			texture_menu->material_preview})
		|| !textfield_change_limit(texture_menu->texture_scale_u_textfield, 10)
		|| !textfield_change_default_text(texture_menu->
			texture_scale_u_textfield, "Float")
		|| !container_add(container, texture_menu->texture_scale_u_textfield)
		|| !(texture_menu->texture_scale_v_label = create_label(vec2i(165,
			240 + 50), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->texture_scale_v_label, "V")
		|| !container_add(container, texture_menu->texture_scale_v_label))
		return (false);
	return (internal_texture_menu_6(container, texture_menu, env));
}
