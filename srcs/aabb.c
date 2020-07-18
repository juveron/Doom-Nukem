/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 20:25:49 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/12 20:25:49 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_aabb(t_aabb *aabb)
{
	aabb->xmax = -INFINITY;
	aabb->ymax = -INFINITY;
	aabb->xmin = INFINITY;
	aabb->ymin = INFINITY;
}

void	update_aabb(t_aabb *aabb, t_vec3f *vec)
{
	if (aabb->xmin > vec->x)
		aabb->xmin = vec->x;
	if (aabb->xmax < vec->x)
		aabb->xmax = vec->x;
	if (aabb->ymin > vec->z)
		aabb->ymin = vec->z;
	if (aabb->ymax < vec->z)
		aabb->ymax = vec->z;
}

bool	inside_aabb(t_aabb *aabb, t_vec2f *vec)
{
	return (aabb->xmin <= vec->x && aabb->xmax >= vec->x
		&& aabb->ymin <= vec->y && aabb->ymax >= vec->y);
}
