/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:42:55 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/16 14:43:06 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	free_all_scene(t_env *env)
{
	free_scene(&env->scenes.main_menu);
	free_scene(&env->scenes.editor);
	free_scene(&env->scenes.game);
}
