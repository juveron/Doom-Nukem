/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision_p3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:19:32 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 15:30:24 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision_internal.h"

int	check_collision_p9(t_collision_handler *handler, t_env *env)
{
	size_t	i;
	size_t	size;

	handler->in = false;
	i = 0;
	if (env->app_state == APP_EDITOR_GAME)
		size = env->current_map->sectors->total;
	else
		size = env->game->visible_sector.total;
	while (i < size)
	{
		if (!check_collision_p2(env, handler, i++))
			return (1);
		check_collision_p5(env, handler);
	}
	if (!check_collision_p8(env, handler))
		return (1);
	return (0);
}
