/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:48:16 by thboura           #+#    #+#             */
/*   Updated: 2020/07/16 15:16:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector_menu_internal.h"
#include "editor.h"

bool		destroy_sector_menu(t_sector_menu *sector_menu)
{
	int ret;

	ret = 0;
	ret += !destroy_check_box(&sector_menu->floor_damage_check_box);
	ret += !destroy_label(&sector_menu->floor_damage_label);
	ret += !destroy_check_box(&sector_menu->has_roof_check_box);
	ret += !destroy_label(&sector_menu->has_roof_label);
	ret += !destroy_textfield(&sector_menu->ceil_level_textfield);
	ret += !destroy_label(&sector_menu->ceil_level_label);
	ret += !destroy_textfield(&sector_menu->floor_level_textfield);
	ret += !destroy_label(&sector_menu->floor_level_label);
	ret += !destroy_container(&sector_menu->container);
	return (ret == 0);
}

static bool	change_floor_level(void *text, void *param)
{
	t_sector_menu	*sector_menu;
	char			limit[100];

	sector_menu = param;
	sector_menu->sector->floor = ft_atof(text);
	if (sector_menu->sector->floor < -1000 || sector_menu->sector->floor > 1000)
	{
		sector_menu->sector->floor = clampf(sector_menu->sector->floor, -1000,
			1000);
		ft_snprintf(limit, sizeof(limit), "%f", sector_menu->sector->floor);
		if (!textfield_change_value(sector_menu->floor_level_textfield, limit))
			return (false);
	}
	update_height(sector_menu->sector, sector_menu->env);
	vector_free(&sector_menu->sector->triangle_bottom);
	if (sector_menu->sector->has_roof)
		vector_free(&sector_menu->sector->triangle_top);
	if (!triangulate_sector(sector_menu->sector))
		return (false);
	if (!triangulate_all_neighbor(sector_menu->sector))
		return (false);
	return (true);
}

bool		create_sector_menu(t_sector_menu *sector_menu, t_env *env)
{
	ft_bzero(sector_menu, sizeof(t_sector_menu));
	if (!(sector_menu->container = create_container((SDL_Rect){0, 370 + 50,
			600, 380}, false, 0))
		|| !(sector_menu->floor_level_label = create_label(vec2i(20, 10 + 50),
			0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(sector_menu->floor_level_label, "Floor level")
		|| !container_add(sector_menu->container,
			&sector_menu->floor_level_label->component)
		|| !(sector_menu->floor_level_textfield = create_textfield(
			(SDL_Rect){140, 0 + 50, 115, 40}, 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16))
		|| !textfield_change_limit(sector_menu->floor_level_textfield, 10)
		|| !textfield_change_default_text(sector_menu->floor_level_textfield,
			"Float")
		|| !add_custom_action(sector_menu->floor_level_textfield->
			on_text_change, &(t_custom_event){&change_floor_level,
			sector_menu})
		|| !container_add(sector_menu->container,
			&sector_menu->floor_level_textfield->component)
		|| !create_sector_menu_p2(sector_menu, env))
	{
		destroy_sector_menu(sector_menu);
		return (false);
	}
	return (true);
}

static bool	init_sector_menu_p2(t_sector_menu *menu, t_env *env)
{
	char	buff[256];

	env->gui.status = GUI_SECTOR;
	ft_snprintf(buff, sizeof(buff), "%f", menu->sector->floor);
	if (!textfield_change_value(menu->floor_level_textfield, buff))
		return (false);
	ft_snprintf(buff, sizeof(buff), "%f", menu->sector->ceil);
	if (!textfield_change_value(menu->ceil_level_textfield, buff))
		return (false);
	check_box_enable(menu->has_roof_check_box, menu->sector->has_roof);
	check_box_enable(menu->floor_damage_check_box, menu->sector->floor_damage);
	return (true);
}

bool		init_sector_menu(t_sector_menu *menu, t_sector *sector, bool floor,
	t_env *env)
{
	menu->sector = sector;
	menu->env = env;
	if (env->gui.status != GUI_SECTOR)
	{
		if (!container_clear(env->gui.window->container)
			|| !container_add(env->gui.window->container,
				&env->gui.material_menu->container->component)
			|| !container_add(env->gui.window->container,
			&env->gui.sector_menu.container->component))
			return (false);
		env->gui.window->container->component.need_redraw = true;
	}
	if (floor)
	{
		if (!init_texture_menu(env->gui.material_menu, sector->mtl_floor))
			return (false);
	}
	else
	{
		if (!init_texture_menu(env->gui.material_menu, sector->mtl_ceil))
			return (false);
	}
	return (init_sector_menu_p2(menu, env));
}
