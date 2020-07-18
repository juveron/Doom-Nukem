/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 10:58:43 by thboura           #+#    #+#             */
/*   Updated: 2020/03/07 17:31:07 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	check_if_already_exists(t_env *env, t_vec3f *position)
{
	if ((env->current_map->level.start.available
		&& env->current_map->level.start.position.x == position->x
		&& env->current_map->level.start.position.z == position->z)
		|| (env->current_map->level.end.available
		&& (env->current_map->level.end.position.x == position->x
		&& env->current_map->level.end.position.z == position->z)))
		return (true);
	return (false);
}
