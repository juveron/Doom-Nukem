/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 00:18:58 by kguibout          #+#    #+#             */
/*   Updated: 2019/07/30 12:56:53 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "window.h"

void	blit_surface(SDL_Surface *surface, SDL_Rect rect, t_window *win)
{
	SDL_BlitSurface(surface, NULL, win->surface, &rect);
}
