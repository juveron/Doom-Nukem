/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:09:11 by kguibout          #+#    #+#             */
/*   Updated: 2020/02/28 13:43:27 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_point	*point_clone(t_point *point)
{
	t_point		*point_tmp;

	if (!(point_tmp = malloc(sizeof(t_point))))
		return (NULL);
	point_tmp->id = point->id;
	point_tmp->v = point->v;
	if (!map_clone(&point_tmp->sector, point->sector))
	{
		free(point_tmp);
		return (NULL);
	}
	return (point_tmp);
}

void	point_free(t_point *point)
{
	if (!point)
		return ;
	map_free(point->sector);
	free(point);
}
