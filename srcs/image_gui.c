/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_gui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:05:56 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/19 12:17:00 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	load_image_for_gui(t_env *env)
{
	if (!(env->gui_image.up_arrow_30x30 = import_tga("./assets/up_arrow.tga",
			false))
	|| !(env->gui_image.down_arrow_30x30 = import_tga("./assets/down_arrow.tga",
			false))
	|| !(env->gui_image.plus_30x30 = import_tga("./assets/plus.tga",
			false))
	|| !(env->gui_image.button_background_1 = import_tga("./assets/button.tga",
			false)))
		throw_error("Failed to load fonts !", env);
}

void	free_image_for_gui(t_env *env)
{
	SDL_FreeSurface(env->gui_image.up_arrow_30x30);
	SDL_FreeSurface(env->gui_image.down_arrow_30x30);
	SDL_FreeSurface(env->gui_image.plus_30x30);
	SDL_FreeSurface(env->gui_image.button_background_1);
}
