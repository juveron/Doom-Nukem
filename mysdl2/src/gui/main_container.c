/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:29:08 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 23:23:22 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool	init_main_container(t_window *window)
{
	if (!(window->main_container = create_container((SDL_Rect){0, 0,
		window->size.x, window->size.y}, false, 0)))
		return (false);
	window->main_container->component.elem_type = GUI_ELEM_MAIN_CONTAINER;
	window->main_container->component.parent = NULL;
	window->main_container->component.is_visible = true;
	return (true);
}
