/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 10:26:04 by kguibout          #+#    #+#             */
/*   Updated: 2019/07/30 12:56:51 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel.h"

/*
** Get pixel from surface (WARNING: Only surface on 4 bytes are supported !).
**
** \param   pos Pointer to position of the pixel
** \param   surface The SDL_Surface
**
** \return  Color of the pixel
*/

t_color	get_pixel(t_vec2i *pos, SDL_Surface *surface)
{
	return (((t_u32 *)surface->pixels)[pos->y * surface->w + pos->x]);
}

/*
** Set pixel on surface (WARNING: Only surface on 4 bytes are supported !).
**
** \param   pos Pointer to position of the pixel
** \param   color Color of the pixel
** \param   surface The SDL_Surface
*/

void	set_pixel(t_vec2i *pos, t_color color, SDL_Surface *surface)
{
	((t_u32 *)surface->pixels)[pos->y * surface->w + pos->x] = color;
}
