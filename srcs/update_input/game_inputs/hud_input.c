/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:10:33 by juveron           #+#    #+#             */
/*   Updated: 2020/06/17 18:21:28 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	hud_input(t_env *env)
{
	if (get_key_down(SDL_SCANCODE_COMMA) && env->hud.nb_heal > 0)
		env->hud.nb_heal--;
	if (get_key_down(SDL_SCANCODE_PERIOD) && env->hud.nb_heal < 3)
		env->hud.nb_heal++;
	if (get_key_down(SDL_SCANCODE_R))
		clock_restart(&env->hud.time);
	if (get_key_down(SDL_SCANCODE_TAB))
	{
		env->hud.rend = !env->hud.rend;
	}
}
