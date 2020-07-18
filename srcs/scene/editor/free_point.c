/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 11:33:31 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 12:47:21 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	free_point(t_point *point)
{
	if (!point)
		return ;
	map_free(point->sector);
	free(point);
}
