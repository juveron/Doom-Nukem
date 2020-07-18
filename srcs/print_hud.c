/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 17:30:37 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/10 23:58:35 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_hud(t_env *env)
{
	env->hud.nb_heal = 3;
	env->hud.objs_in_map.remaining = UINT64_MAX;
	env->hud.rend = 1;
	clock_restart(&env->hud.time);
}

bool	create_hud(t_env *env)
{
	if (!(env->hud.heal = import_tga("./assets/heart.tga", false)))
		return (false);
	return (true);
}

bool	print_hud(t_env *env)
{
	int				i;

	i = 0;
	while (i < env->hud.nb_heal)
	{
		blit_surface(env->hud.heal,
			(SDL_Rect){50 + 60 * i, 50, 0, 0}, env->main_window);
		i++;
	}
	if (!blit_clock(env)
		|| !blit_objects(env, &env->hud.objs_in_map))
		return (false);
	return (true);
}

bool	hud_off_on(t_env *env)
{
	if (env->hud.rend == 1 && env->gui.status != GUI_PAUSE)
		return (print_hud(env));
	return (true);
}

bool	update_damage(t_env *env)
{
	env->hud.nb_heal -= 1;
	if (env->hud.nb_heal == 0)
	{
		if (!init_game_over(env))
			return (false);
		if (env->game_over.active)
			return (start_game_over_animation(env));
		else
			return (init_game_over_menu(env));
	}
	else
		teleport_to_spawn(env);
	return (true);
}
