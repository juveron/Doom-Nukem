/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 13:01:06 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 14:47:39 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_INTERNAL_H
# define HISTORY_INTERNAL_H

# include "doom_nukem.h"

t_gui_event_selection	*create_event_selection(t_env *env, SDL_Rect rect,
	t_recorded_event_handler *event_handler);

t_dlist					*get_dlist_by_index(t_dlist_handler *list,
	size_t index);
size_t					get_dlist_index(t_dlist_handler *list, t_dlist *dlist);
bool					set_selected_event(t_gui_event_selection *selection,
	t_dlist *tmp_dlist, size_t index);
bool					draw_event_selection_func(void *param);

#endif
