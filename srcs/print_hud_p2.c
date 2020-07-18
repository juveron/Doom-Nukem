/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hud_p2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:07:55 by thboura           #+#    #+#             */
/*   Updated: 2020/07/16 12:42:23 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	blit_clock(t_env *env)
{
	SDL_Surface		*surface;
	char			buffer[32];

	ft_snprintf(buffer, sizeof(buffer), "%02d:%02d:%02lu",
		(int)clock_get_seconds(&env->hud.time) / 60 % 60,
			(int)clock_get_seconds(&env->hud.time) % 60,
				clock_get_milliseconds(&env->hud.time) % 1000 / 10);
	if (!(surface = TTF_RenderText_Blended(env->fonts.deja_vu_sans_momo_30,
		buffer, (SDL_Color){255, 255, 255, 0})))
		return (false);
	blit_surface(surface,
		(SDL_Rect){WIDTH / 2 - surface->w / 2, 10, 0, 0}, env->main_window);
	SDL_FreeSurface(surface);
	return (true);
}

bool	blit_objects(t_env *env, t_objs_in_map *objs)
{
	char	buffer[32];

	if (objs->remaining != env->objects_manager.remaining_object.total)
	{
		if (env->objects_manager.remaining_object.total > 0)
			ft_snprintf(buffer, sizeof(buffer), "Remaining fragments : %lu",
				env->objects_manager.remaining_object.total);
		else
			ft_snprintf(buffer, sizeof(buffer), "No remaining fragments");
		SDL_FreeSurface(objs->surface);
		if (!(objs->surface = TTF_RenderText_Blended(
			env->fonts.deja_vu_sans_momo_30, buffer,
			(SDL_Color){255, 255, 255, 0})))
			return (false);
		objs->remaining = env->objects_manager.remaining_object.total;
	}
	blit_surface(objs->surface, (SDL_Rect){WIDTH - objs->surface->w,
			0, 0, 0}, env->main_window);
	return (true);
}

void	destroy_hud(t_env *env)
{
	SDL_FreeSurface(env->hud.objs_in_map.surface);
	env->hud.objs_in_map.surface = NULL;
	SDL_FreeSurface(env->hud.heal);
}
