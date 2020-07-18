/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recorded_insert_point_p2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:45:41 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 18:45:41 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool	insert_by_correct_wall(t_wall *verif_wall, t_wall *src_wall,
		t_sector *sector, size_t *i)
{
	t_wall	*walls;

	walls = (t_wall *)sector->walls.items;
	while (*i < sector->walls.total)
	{
		if (&walls[*i] == verif_wall)
		{
			if (vector_insert(&sector->walls, *i + 1, src_wall))
				return (true);
			else
				return (false);
		}
		(*i)++;
	}
	return (false);
}
