/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 00:55:29 by killian           #+#    #+#             */
/*   Updated: 2019/07/04 11:15:25 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "window.h"
#include "line.h"
#include <math.h>

static int	init_line(t_vec2i start, t_vec2i end, t_line *line,
	SDL_Surface *surface)
{
	if ((start.x < 0 && end.x < 0) || (start.y < 0 && end.y < 0)
		|| (start.x >= surface->w && end.x >= surface->w)
		|| (start.y >= surface->h && end.y >= surface->h))
		return (0);
	line->d.x = abs(end.x - start.x);
	line->d.y = -abs(end.y - start.y);
	line->s.x = start.x < end.x ? 1 : -1;
	line->s.y = start.y < end.y ? 1 : -1;
	line->err = line->d.x + line->d.y;
	return (1);
}

void		draw_line(t_vec2i start, t_vec2i end, int color,
	SDL_Surface *surface)
{
	t_line	line;

	if (!init_line(start, end, &line, surface))
		return ;
	while (1)
	{
		if (!(start.x < 0 || start.x >= surface->w
				|| start.y < 0 || start.y >= surface->h))
			((t_u32 *)(surface->pixels))[start.x + start.y
				* surface->w] = color;
		if (start.x == end.x && start.y == end.y)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.d.y)
		{
			line.err += line.d.y;
			start.x += line.s.x;
		}
		if (line.e2 <= line.d.x)
		{
			line.err += line.d.x;
			start.y += line.s.y;
		}
	}
}
