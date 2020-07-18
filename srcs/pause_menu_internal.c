/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu_internal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:40:19 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 11:11:31 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	on_enter_pause_menu(void *param)
{
	t_gui_button	*button;

	button = param;
	button->component.background = 0x333333FF;
	button->component.need_redraw = true;
	return (true);
}

bool	on_leave_pause_menu(void *param)
{
	t_gui_button	*button;

	button = param;
	button->component.background = 0x777777FF;
	button->component.need_redraw = true;
	return (true);
}
