/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 19:46:04 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 19:46:04 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	teleport_to_spawn(t_env *env)
{
	if (env->current_map->level.start.available)
	{
		env->player.transform->position = env->current_map->level.start.
				position;
		env->player.transform->rotation.y = env->current_map->
				level.start.rotation;
		env->player.transform->rotation.x = 0;
		env->player.transform->rotation.z = 0;
	}
}
