/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_clip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:12:50 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 15:27:55 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

static t_outcode	compute_outcode(t_clipping_line *line, t_vec2i v)
{
	t_outcode code;

	code = CS_INSIDE;
	if (v.x < line->bound_min.x)
		code |= CS_LEFT;
	else if (v.x > line->bound_max.x)
		code |= CS_RIGHT;
	if (v.y < line->bound_min.y)
		code |= CS_BOTTOM;
	else if (v.y > line->bound_max.y)
		code |= CS_TOP;
	return (code);
}

static void			draw_line_clip_p3(t_clipping_line *line,
	t_outcode *outcode_out, double *x, double *y)
{
	if (*outcode_out & CS_TOP)
	{
		*x = (*line).v0.x + ((*line).v1.x - (*line).v0.x) * ((*line).bound_max.y
			- (*line).v0.y) / ((*line).v1.y - (*line).v0.y);
		*y = (*line).bound_max.y;
	}
	else if (*outcode_out & CS_BOTTOM)
	{
		*x = (*line).v0.x + ((*line).v1.x - (*line).v0.x) * ((*line).bound_min.y
			- (*line).v0.y) / ((*line).v1.y - (*line).v0.y);
		*y = (*line).bound_min.y;
	}
	else if (*outcode_out & CS_RIGHT)
	{
		*y = (*line).v0.y + ((*line).v1.y - (*line).v0.y) * ((*line).bound_max.x
			- (*line).v0.x) / ((*line).v1.x - (*line).v0.x);
		*x = (*line).bound_max.x;
	}
	else if (*outcode_out & CS_LEFT)
	{
		*y = (*line).v0.y + ((*line).v1.y - (*line).v0.y) * ((*line).bound_min.x
			- (*line).v0.x) / ((*line).v1.x - (*line).v0.x);
		*x = (*line).bound_min.x;
	}
}

static void			draw_line_clip_p2(t_clipping_line *line,
	t_outcode *outcode0, t_outcode *outcode1)
{
	double		x;
	double		y;
	t_outcode	outcode_out;

	outcode_out = *outcode0 ? *outcode0 : *outcode1;
	draw_line_clip_p3(line, &outcode_out, &x, &y);
	if (outcode_out == *outcode0)
	{
		(*line).v0.x = x;
		(*line).v0.y = y;
		*outcode0 = compute_outcode(line, (*line).v0);
	}
	else
	{
		(*line).v1.x = x;
		(*line).v1.y = y;
		*outcode1 = compute_outcode(line, (*line).v1);
	}
}

void				draw_line_clip(t_clipping_line line, int color,
	SDL_Surface *surface)
{
	t_outcode	outcode0;
	t_outcode	outcode1;
	int			accept;

	outcode0 = compute_outcode(&line, line.v0);
	outcode1 = compute_outcode(&line, line.v1);
	accept = 0;
	while (1)
	{
		if (!(outcode0 | outcode1))
		{
			accept = 1;
			break ;
		}
		else if (outcode0 & outcode1)
			break ;
		else
			draw_line_clip_p2(&line, &outcode0, &outcode1);
	}
	if (accept)
		draw_line(line.v0, line.v1, color, surface);
}
