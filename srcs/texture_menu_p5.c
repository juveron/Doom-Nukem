/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_menu_p5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:11:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/13 12:11:06 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "texture_menu_internal.h"

bool	copy_material(void *param)
{
	t_material_menu *texture_menu;

	texture_menu = param;
	mtl_destroy(&texture_menu->env->editor.copy.material);
	if (!(texture_menu->env->editor.copy.material = mtl_clone(texture_menu->
			material)))
		return (false);
	return (true);
}

bool	past_material(void *param)
{
	t_material_menu *texture_menu;

	texture_menu = param;
	if (!texture_menu->env->editor.copy.material)
		return (true);
	if (!remove_material_from_texture(texture_menu->material->diffuse_texture,
			texture_menu->material))
		return (false);
	*texture_menu->material = *texture_menu->env->editor.copy.material;
	if (texture_menu->material->diffuse_texture
		&& !add_material_to_texture(texture_menu->material->diffuse_texture,
			texture_menu->material))
		return (false);
	init_texture_menu(texture_menu, texture_menu->material);
	return (true);
}
