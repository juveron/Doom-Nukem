/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:20:25 by thboura           #+#    #+#             */
/*   Updated: 2020/06/13 15:27:34 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	free_wall(t_wall *wall)
{
	if (!wall)
		return ;
	mtl_destroy(&wall->mtl_bottom);
	mtl_destroy(&wall->mtl_top);
}

t_wall	*wall_clone(t_wall *wall)
{
	t_wall	*ret_wall;

	if (!(ret_wall = (t_wall *)malloc(sizeof(t_wall))))
		return (NULL);
	*ret_wall = *wall;
	if (wall->neighbor)
		ret_wall->neighbor = (t_sector *)wall->neighbor->id;
	else
		ret_wall->neighbor = (t_sector *)-1;
	ret_wall->v1 = (t_point *)wall->v1->id;
	ret_wall->v2 = (t_point *)wall->v2->id;
	if (!(ret_wall->mtl_bottom = mtl_clone(wall->mtl_bottom))
		|| !(ret_wall->mtl_top = mtl_clone(wall->mtl_top)))
	{
		free_wall(ret_wall);
		return (NULL);
	}
	return (ret_wall);
}

void	free_wall_event(t_wall *wall)
{
	if (!wall)
		return ;
	mtl_destroy(&wall->mtl_bottom);
	mtl_destroy(&wall->mtl_top);
	free(wall);
}

void	free_walls_sector(t_vector *walls_vector)
{
	size_t	i;
	t_wall	*walls;

	walls = walls_vector->items;
	i = 0;
	while (i < walls_vector->total)
	{
		mtl_destroy(&walls[i].mtl_bottom);
		mtl_destroy(&walls[i].mtl_top);
		i++;
	}
	vector_free(walls_vector);
}
