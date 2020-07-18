/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:48:01 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 16:25:33 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**	if neighbor set existing vertex index
*/

bool	point_add_sector(t_point *point, t_sector *sector)
{
	return (map_add(point->sector, sector->id, &sector));
}

bool	point_remove_sector(t_point *point, t_sector *sector)
{
	return (map_delete(point->sector, sector->id));
}
