/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 00:35:41 by kguibout          #+#    #+#             */
/*   Updated: 2019/06/26 15:35:12 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "pixel.h"

static void	draw_rectangle_width(SDL_Rect rect, int color, SDL_Surface *surface,
	int j)
{
	int		i;
	t_vec2i	pos;

	i = 0;
	pos.y = rect.y + j;
	while (i < rect.w)
	{
		if (i + rect.x < 0)
		{
			i++;
			continue ;
		}
		else if (i + rect.x >= surface->w)
			break ;
		pos.x = rect.x + i;
		set_pixel(&pos, color, surface);
		i++;
	}
}

void		draw_rectangle(SDL_Rect rect, int color, SDL_Surface *surface)
{
	int		j;

	j = 0;
	while (j < rect.h)
	{
		if (j + rect.y < 0)
		{
			j++;
			continue ;
		}
		else if (j + rect.y >= surface->h)
			break ;
		draw_rectangle_width(rect, color, surface, j);
		j++;
	}
}
