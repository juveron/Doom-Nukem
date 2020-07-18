/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 01:10:03 by killian           #+#    #+#             */
/*   Updated: 2020/05/30 22:18:31 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "libft.h"
# include <SDL2/SDL.h>

# define CS_INSIDE	0
# define CS_LEFT	1
# define CS_RIGHT	2
# define CS_BOTTOM	4
# define CS_TOP		8

typedef struct	s_clipping_line
{
	t_vec2i	v0;
	t_vec2i	v1;
	t_vec2i	bound_min;
	t_vec2i	bound_max;
}				t_clipping_line;

typedef int		t_outcode;

void			draw_line(t_vec2i start, t_vec2i end, int color,
	SDL_Surface *surface);
void			draw_line_clip(t_clipping_line line, int color,
	SDL_Surface *surface);
void			draw_rectangle(SDL_Rect rect, int color, SDL_Surface *surface);
void			draw_elipse(SDL_Rect rect, int	color, SDL_Surface *surface);

#endif
