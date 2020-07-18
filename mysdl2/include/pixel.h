/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 10:27:13 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/30 23:25:50 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_H
# define PIXEL_H

# include "libft.h"
# include <SDL2/SDL.h>

typedef unsigned int	t_color;

typedef enum	e_pixel_format
{
	ARGB_PIXEL_FORMAT,
	RGB_PIXEL_FORMAT
}				t_pixel_format;

t_color get_pixel(t_vec2i *pos, SDL_Surface *surface);
void	set_pixel(t_vec2i *pos, t_color color, SDL_Surface *surface);

#endif
