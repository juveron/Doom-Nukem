/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 10:15:15 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/25 17:43:05 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	init_fonts(t_env *env)
{
	if (!(env->fonts.deja_vu_sans_momo_16 = TTF_OpenFont(
			"./assets/DejaVuSansMono.ttf", 16))
		|| !(env->fonts.deja_vu_sans_momo_30 = TTF_OpenFont(
			"./assets/DejaVuSansMono.ttf", 30))
		|| !(env->fonts.deja_vu_sans_momo_60 = TTF_OpenFont(
			"./assets/DejaVuSansMono.ttf", 60))
		|| !(env->fonts.covid_virus_120 = TTF_OpenFont(
			"./assets/CovidVirus.ttf", 120))
		|| !(env->fonts.badabb_120 = TTF_OpenFont(
			"./assets/badabb.ttf", 120)))
	{
		return (false);
	}
	return (true);
}

void	free_fonts(t_env *env)
{
	TTF_CloseFont(env->fonts.deja_vu_sans_momo_16);
	TTF_CloseFont(env->fonts.deja_vu_sans_momo_30);
	TTF_CloseFont(env->fonts.deja_vu_sans_momo_60);
	TTF_CloseFont(env->fonts.covid_virus_120);
	TTF_CloseFont(env->fonts.badabb_120);
}
