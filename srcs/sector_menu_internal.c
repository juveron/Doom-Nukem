/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_menu_internal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:52:25 by thboura           #+#    #+#             */
/*   Updated: 2020/07/16 15:23:22 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector_menu_internal.h"

static bool	change_roof(void *text, void *param)
{
	t_sector_menu	*sector_menu;
	bool			*checked;

	sector_menu = param;
	checked = text;
	vector_free(&sector_menu->sector->triangle_bottom);
	if (sector_menu->sector->has_roof)
		vector_free(&sector_menu->sector->triangle_top);
	sector_menu->sector->has_roof = *checked;
	if (!triangulate_sector(sector_menu->sector))
		return (false);
	return (true);
}

static bool	create_sector_menu_p3(t_sector_menu *sector_menu, t_env *env)
{
	if (!(sector_menu->has_roof_label = create_label(vec2i(20, 105 + 50),
			0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(sector_menu->has_roof_label, "Has roof ?")
		|| !container_add(sector_menu->container,
			&sector_menu->has_roof_label->component)
		|| !(sector_menu->has_roof_check_box = create_check_box((SDL_Rect){140,
			100 + 50, 30, 30}, 0x333333FF))
		|| !(add_custom_action(sector_menu->has_roof_check_box->on_toggle,
			&(t_custom_event){&change_roof, sector_menu}))
		|| !container_add(sector_menu->container,
			&sector_menu->has_roof_check_box->component)
		|| !create_sector_menu_p4(sector_menu, env))
		return (false);
	return (true);
}

static bool	change_ceil_level(void *text, void *param)
{
	t_sector_menu	*sector_menu;
	char			limit[100];

	sector_menu = param;
	sector_menu->sector->ceil = ft_atof(text);
	if (sector_menu->sector->ceil < 0 || sector_menu->sector->ceil > 100)
	{
		sector_menu->sector->ceil = clampf(sector_menu->sector->ceil, 0,
			100);
		ft_snprintf(limit, sizeof(limit), "%f", sector_menu->sector->ceil);
		if (!textfield_change_value(sector_menu->ceil_level_textfield, limit))
			return (false);
	}
	vector_free(&sector_menu->sector->triangle_bottom);
	if (sector_menu->sector->has_roof)
		vector_free(&sector_menu->sector->triangle_top);
	if (!triangulate_sector(sector_menu->sector))
		return (false);
	if (!triangulate_all_neighbor(sector_menu->sector))
		return (false);
	return (true);
}

bool		create_sector_menu_p2(t_sector_menu *sector_menu, t_env *env)
{
	if (!(sector_menu->ceil_level_label = create_label(vec2i(20, 60 + 50),
			0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(sector_menu->ceil_level_label, "Ceil height")
		|| !container_add(sector_menu->container,
			&sector_menu->ceil_level_label->component)
		|| !(sector_menu->ceil_level_textfield = create_textfield((SDL_Rect)
			{140, 50 + 50, 115, 40}, 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16))
		|| !textfield_change_limit(sector_menu->ceil_level_textfield, 10)
		|| !textfield_change_default_text(sector_menu->ceil_level_textfield,
			"Float")
		|| !add_custom_action(sector_menu->ceil_level_textfield->
			on_text_change, &(t_custom_event){&change_ceil_level, sector_menu})
		|| !container_add(sector_menu->container,
			&sector_menu->ceil_level_textfield->component)
		|| !create_sector_menu_p3(sector_menu, env))
		return (false);
	return (true);
}
