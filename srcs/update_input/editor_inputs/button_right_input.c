/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_right_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:37:41 by thboura           #+#    #+#             */
/*   Updated: 2020/02/28 10:20:00 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

void	button_right_input(t_env *env)
{
	t_vec2i		mouse_pos;
	t_vec2f		map_pos;
	t_sector	*sector;

	if (get_button_down(SDL_BUTTON_RIGHT, NULL))
	{
		mouse_pos = get_mouse_position();
		map_pos = win_to_map(&mouse_pos, env);
		if ((sector = is_in_sector(env, &map_pos, true)))
		{
			set_visible(&env->gui.window->component, true);
			init_sector_menu(&env->gui.sector_menu, sector, true, env);
		}
		else
		{
			set_visible(&env->gui.window->component, false);
			set_visible(&env->gui.texture_menu->window->component, false);
		}
		env->need_redraw = true;
	}
}
