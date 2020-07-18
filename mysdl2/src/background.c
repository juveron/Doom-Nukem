/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 23:19:31 by killian           #+#    #+#             */
/*   Updated: 2019/05/20 23:56:30 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "window.h"

void	set_color_background(t_u32 color, t_window *win)
{
	int		i;

	i = 0;
	while (i < win->surface->h * win->surface->w)
	{
		((t_u32 *)(win->surface->pixels))[i] = color;
		i++;
	}
}
