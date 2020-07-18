/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:20:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/06 04:16:42 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void	free_window(void)
{
	t_context	*context;
	size_t		size_map;
	size_t		i;
	t_window	*win;

	context = get_context();
	size_map = map_total(context->window);
	i = 0;
	while (i < size_map)
	{
		win = (t_window *)context->window->elem[i].data;
		destroy_window(win);
		map_delete(context->window, win->id);
		i++;
	}
	map_free(context->window);
}
