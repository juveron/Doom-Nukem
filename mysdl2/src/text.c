/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 09:39:29 by kguibout          #+#    #+#             */
/*   Updated: 2019/07/19 12:35:57 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "text.h"
#include "context.h"
#include "window.h"

/*
** Create surface with text.
**
** \param   text  Text to write
** \param   color  Color of the text
**
** \return  Pointer to an SDL_Surface, NULL if error occurs.
*/

SDL_Surface	*text_surface(char *text, int color, TTF_Font *font)
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Blended(font, text,
		(SDL_Color){.r = (color >> 24) & 0xFF, .g = (color >> 16) & 0xFF,
		.b = (color >> 8) & 0xFF, .a = color & 0xFF});
	return (text_surface);
}
