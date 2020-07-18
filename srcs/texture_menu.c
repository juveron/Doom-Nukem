/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:11:54 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 15:52:42 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "texture_menu_internal.h"

static bool		internal_texture_menu_4(t_container *container,
	t_material_menu *texture_menu, t_env *env)
{
	if (!(texture_menu->texture_pos_v_textfield = create_textfield(
			(SDL_Rect){185, 150 + 50, 115, 40}, 0xFFFFFFFF, env->fonts.
			deja_vu_sans_momo_16))
		|| !add_custom_action(texture_menu->texture_pos_v_textfield->
			on_text_change, &(t_custom_event){&change_v_texture_pos,
			texture_menu->material_preview})
		|| !textfield_change_limit(texture_menu->texture_pos_v_textfield, 10)
		|| !textfield_change_default_text(texture_menu->
			texture_pos_v_textfield, "Float")
		|| !container_add(container, texture_menu->texture_pos_v_textfield)
		|| !(texture_menu->texture_scale_label = create_label(vec2i(20,
			200 + 50), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->texture_scale_label,
			"Texture Scale"))
		return (false);
	texture_menu->texture_scale_label->component.rect.x = 150
			- texture_menu->texture_scale_label->component.rect.w / 2;
	if (!container_add(container, texture_menu->texture_scale_label)
		|| !(texture_menu->texture_scale_u_label = create_label(vec2i(20,
			240 + 50), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->texture_scale_u_label, "U")
		|| !container_add(container, texture_menu->texture_scale_u_label))
		return (false);
	return (internal_texture_menu_5(container, texture_menu, env));
}

static bool		internal_texture_menu_3(t_container *container,
	t_material_menu *texture_menu, t_env *env)
{
	if (!(texture_menu->texture_pos_u_textfield = create_textfield((SDL_Rect){
			40, 150 + 50, 115, 40}, 0xFFFFFFFF, env->fonts.
			deja_vu_sans_momo_16))
		|| !add_custom_action(texture_menu->texture_pos_u_textfield->
			on_text_change, &(t_custom_event){&change_u_texture_pos,
			texture_menu->material_preview})
		|| !textfield_change_limit(texture_menu->texture_pos_u_textfield, 10)
		|| !textfield_change_default_text(texture_menu->
			texture_pos_u_textfield, "Float")
		|| !container_add(container, texture_menu->texture_pos_u_textfield)
		|| !(texture_menu->texture_pos_v_label = create_label(vec2i(165, 160
			+ 50), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->texture_pos_v_label, "V")
		|| !container_add(container, texture_menu->texture_pos_v_label))
		return (false);
	return (internal_texture_menu_4(container, texture_menu, env));
}

static bool		internal_texture_menu_2(t_container *container,
	t_material_menu *texture_menu, t_env *env)
{
	if (!(texture_menu->texture_pos_label = create_label(vec2i(20, 120 + 50),
			0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->texture_pos_label, "Texture Pos")
		|| !(texture_menu->texture_pos_label->component.rect.x = 150
			- texture_menu->texture_pos_label->component.rect.w / 2)
		|| !container_add(container, texture_menu->texture_pos_label)
		|| !(texture_menu->texture_pos_u_label = create_label(vec2i(20,
			160 + 50), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->texture_pos_u_label, "U")
		|| !container_add(container, texture_menu->texture_pos_u_label))
		return (false);
	return (internal_texture_menu_3(container, texture_menu, env));
}

static bool		internal_texture_menu_1(t_container *container,
	t_material_menu *texture_menu, t_env *env)
{
	if (!(texture_menu->diffuse_color_textfield = create_textfield(
			(SDL_Rect){170, 10 + 50, 130, 40}, 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16))
		|| !add_custom_action(texture_menu->diffuse_color_textfield->
			on_text_change, &(t_custom_event){&change_diffuse_color,
			texture_menu->material_preview})
		|| !textfield_change_limit(texture_menu->diffuse_color_textfield, 6)
		|| !textfield_change_default_text(texture_menu->diffuse_color_textfield,
			"Hex Color")
		|| !container_add(container, texture_menu->diffuse_color_textfield)
		|| !(texture_menu->diffuse_texture_label = create_label(vec2i(20,
			70 + 50), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->diffuse_texture_label,
			"Diffuse texture")
		|| !container_add(container, texture_menu->diffuse_texture_label)
		|| !(texture_menu->diffuse_texture_button = create_button(
			(SDL_Rect){190, 60 + 50, 110, 40}, 0x666666FF,
			env->fonts.deja_vu_sans_momo_16))
		|| !button_change_name(texture_menu->diffuse_texture_button,
			"Open Menu")
		|| !container_add(container, texture_menu->diffuse_texture_button))
		return (false);
	return (internal_texture_menu_2(container, texture_menu, env));
}

t_material_menu	*create_texture_menu(t_component *parent, t_env *env)
{
	t_material_menu	*texture_menu;

	if (!(texture_menu = ft_memalloc(sizeof(t_material_menu)))
		|| !(texture_menu->container = create_container((SDL_Rect){0, 0,
			parent->rect.w, parent->rect.h}, false, 0x0))
		|| !(texture_menu->material_preview = create_material_preview(
			(SDL_Rect){320, 60, 260, 260}, env))
		|| !container_add(texture_menu->container,
			texture_menu->material_preview)
		|| !(texture_menu->material_label = create_label(vec2i(270, 20),
			0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->material_label, "Material")
		|| !container_add(texture_menu->container, texture_menu->material_label)
		|| !(texture_menu->diffuse_color_label = create_label(vec2i(20,
			20 + 50), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(texture_menu->diffuse_color_label,
			"Diffuse color")
		|| !container_add(texture_menu->container,
			texture_menu->diffuse_color_label)
		|| !internal_texture_menu_1(texture_menu->container, texture_menu,
			env))
		return (NULL);
	texture_menu->material_label->component.rect.x = 300
		- texture_menu->material_label->component.rect.w / 2;
	return (texture_menu);
}
