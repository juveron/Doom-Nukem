/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:52:09 by thboura           #+#    #+#             */
/*   Updated: 2020/03/07 17:29:59 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_level_point	*get_level_point(t_level_param *level_param,
	t_vec3f *position)
{
	if (level_param->start.available
		&& level_param->start.position.x == position->x
		&& level_param->start.position.z == position->z)
		return (&level_param->start);
	if (level_param->end.available
		&& level_param->end.position.x == position->x
		&& level_param->end.position.z == position->z)
		return (&level_param->end);
	return (NULL);
}
