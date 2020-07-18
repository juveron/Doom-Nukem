/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_menu_p6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:50:55 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 19:55:03 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		create_file_name_label(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->file_name_label = create_label((t_vec2i){300, 600},
		0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF)))
		return (destroy_level_menu(levels_menu));
	if (!label_change_name(levels_menu->file_name_label, "File name"))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->file_name_label))
		return (destroy_level_menu(levels_menu));
	return (true);
}

static bool	rename_file_name(void *text, void *param)
{
	t_map_file				*map_file;

	map_file = param;
	free(map_file->file_name);
	if (((char *)text)[0] == '\0')
	{
		if (!(map_file->file_name = ft_strdup("default_name")))
			return (false);
	}
	else if (!(map_file->file_name = ft_strdup(text)))
		return (false);
	return (true);
}

bool		create_file_name_textfield(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->file_name_textfield = create_textfield((SDL_Rect){400,
		590, 170, 40}, 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	if (!textfield_change_limit(levels_menu->file_name_textfield, 15))
		return (destroy_level_menu(levels_menu));
	if (!textfield_change_default_text(levels_menu->file_name_textfield,
		"file name"))
		return (destroy_level_menu(levels_menu));
	if (!add_custom_action(levels_menu->file_name_textfield->
		on_text_change, &(t_custom_event){rename_file_name, &env->map_file}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container,
		levels_menu->file_name_textfield))
		return (destroy_level_menu(levels_menu));
	return (true);
}
