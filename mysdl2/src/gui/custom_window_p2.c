/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_window_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 23:09:54 by thboura           #+#    #+#             */
/*   Updated: 2020/05/30 23:10:24 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void	custom_window_set_draggable(
	t_gui_custom_window *custom_window, bool enable)
{
	custom_window->is_draggable = enable;
}

bool	destroy_custom_window(t_gui_custom_window **win)
{
	int	ret;

	ret = 0;
	if (*win == NULL)
		return (true);
	ret += !component_remove_from_parent(*win);
	ret += !destroy_container(&(*win)->container);
	destroy_event_handler((*win)->on_window_move);
	destroy_event_handler((*win)->on_window_close);
	SDL_FreeSurface((*win)->surface);
	destroy_component(&(*win)->component);
	free(*win);
	*win = NULL;
	return (ret == 0);
}
