/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_selection_p2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 09:19:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 11:50:48 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	show_texture_window(void *param)
{
	t_env	*env;

	env = param;
	set_visible(&env->gui.texture_menu->window->component,
			env->gui.texture_menu->window->component.is_visible ^ 1);
	init_texture_selection(env->gui.material_menu,
			env->gui.material_menu->material);
	return (true);
}

bool	move_texture_window(void *target, void *param)
{
	t_gui_custom_window	*win1;
	t_gui_custom_window	*win2;

	win1 = target;
	win2 = param;
	win2->component.rect.x = win1->component.rect.x - win2->component.rect.w
		- 10;
	win2->component.rect.y = win1->component.rect.y;
	return (true);
}

bool	close_texture_window(void *target, void *param)
{
	t_gui_custom_window	*win1;

	(void)target;
	win1 = param;
	win1->component.is_visible = false;
	win1->component.parent->need_redraw = true;
	return (true);
}

bool	destroy_select_texture_menu(t_selec_texure_menu *texture_menu)
{
	int	ret;

	ret = 0;
	if (texture_menu == NULL)
		return (true);
	ret += !destroy_button(&texture_menu->delete_button);
	ret += !destroy_label(&texture_menu->texture_name_info);
	ret += !destroy_label(&texture_menu->texture_id_info);
	ret += !destroy_texture_selection(&texture_menu->texture_selection);
	ret += !destroy_container(&texture_menu->container);
	ret += !destroy_custom_window(&texture_menu->window);
	free(texture_menu);
	return (ret == 0);
}
