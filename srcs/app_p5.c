/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_p5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 02:14:23 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 02:14:23 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "game.h"

bool	load_all_scene(t_env *env)
{
	if (!(env->scenes.main_menu = create_main_menu_scene(env)))
		return (false);
	if (!(env->scenes.editor = create_editor_scene(env)))
		return (false);
	if (!(env->scenes.game = create_game_scene(env)))
		return (false);
	return (true);
}
