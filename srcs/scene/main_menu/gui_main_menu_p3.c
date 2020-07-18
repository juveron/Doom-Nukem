/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main_menu_p3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:59:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 17:04:07 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	on_enter(void *param)
{
	t_gui_button	*button;

	button = param;
	button->component.need_redraw = true;
	button->component.use_background = true;
	button->component.background = 0x777777FF;
	return (true);
}

bool	on_leave(void *param)
{
	t_gui_button	*button;

	button = param;
	button->component.need_redraw = true;
	button->component.use_background = false;
	button->component.background = 0xFF0000FF;
	return (true);
}
