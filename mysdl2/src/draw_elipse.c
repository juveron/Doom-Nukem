/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elipse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 23:29:22 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 00:06:40 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"
#include "elipse.h"

static void	draw_elipse_p2(SDL_Rect rect, int color, SDL_Surface *surface,
	t_elipse elipse)
{
	int		y;

	y = 0;
	while (y < rect.h)
	{
		elipse.x1 = elipse.x0 - (elipse.dx - 1);
		while (elipse.x1 > 0)
		{
			if (elipse.x1 * elipse.x1 * elipse.hh + y * y * elipse.ww <= elipse.
				wwhh)
				break ;
			elipse.x1--;
		}
		elipse.dx = elipse.x0 - elipse.x1;
		elipse.x0 = elipse.x1;
		draw_line(vec2i(rect.x + -elipse.x0, rect.y - y),
			vec2i(rect.x + elipse.x0, rect.y - y), color, surface);
		draw_line(vec2i(rect.x + -elipse.x0, rect.y + y),
			vec2i(rect.x + elipse.x0, rect.y + y), color, surface);
		y++;
	}
}

void		draw_elipse(SDL_Rect rect, int color, SDL_Surface *surface)
{
	t_elipse	elipse;

	if (rect.x + rect.w < 0 || rect.x - rect.w >= surface->w
		|| rect.y + rect.h < 0 || rect.y - rect.h >= surface->h)
		return ;
	elipse.hh = rect.h * rect.h;
	elipse.ww = rect.w * rect.w;
	elipse.wwhh = elipse.ww * elipse.hh;
	elipse.x0 = rect.w;
	elipse.dx = 0;
	draw_line(vec2i(rect.x + -rect.w, rect.y), vec2i(rect.x + rect.w, rect.y),
		color, surface);
	draw_elipse_p2(rect, color, surface, elipse);
}
