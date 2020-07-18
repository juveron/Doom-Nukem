/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_menu_internal_p2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:58:42 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 21:59:11 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	change_floor_damage(void *text, void *param)
{
	t_sector_menu	*sector_menu;
	bool			*checked;

	sector_menu = param;
	checked = text;
	sector_menu->sector->floor_damage = *checked;
	return (true);
}

bool		create_sector_menu_p4(t_sector_menu *sector_menu, t_env *env)
{
	if (!(sector_menu->floor_damage_label = create_label(vec2i(20, 135 + 50),
			0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(sector_menu->floor_damage_label,
			"Floor make damage ?")
		|| !container_add(sector_menu->container,
			&sector_menu->floor_damage_label->component)
		|| !(sector_menu->floor_damage_check_box = create_check_box(
			(SDL_Rect){210, 130 + 50, 30, 30}, 0x333333FF))
		|| !add_custom_action(sector_menu->floor_damage_check_box->on_toggle,
			&(t_custom_event){&change_floor_damage, sector_menu})
		|| !container_add(sector_menu->container,
			&sector_menu->floor_damage_check_box->component))
		return (false);
	return (true);
}
