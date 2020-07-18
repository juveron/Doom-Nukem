/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 00:21:50 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:08:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

/*
** Create SDL_Rect.
**
** \param   x x position
** \param   y y position
** \param   w width
** \param   h height
**
** \return  SDL_Rect
*/

SDL_Rect	rect(int x, int y, int w, int h)
{
	return ((SDL_Rect){.x = x, .y = y, .w = w, .h = h});
}

bool		is_in_box(t_vec2i pos, SDL_Rect *rect)
{
	return (!(pos.x < rect->x || pos.x >= rect->x + rect->w
			|| pos.y < rect->y || pos.y >= rect->y + rect->h));
}

bool		is_intersect(SDL_Rect *rect1, SDL_Rect *rect2)
{
	return (!(rect2->x > rect1->x + rect1->w
			|| rect2->x + rect2->w < rect1->x
			|| rect2->y > rect1->y + rect1->h
			|| rect2->y + rect2->h < rect1->y));
}
