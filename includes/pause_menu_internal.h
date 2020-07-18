/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:41:11 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 16:48:55 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAUSE_MENU_INTERNAL_H
# define PAUSE_MENU_INTERNAL_H

# include "doom_nukem.h"

typedef struct	s_pause_menu_handler
{
	SDL_Rect	box;
	t_vec2i		button;
	size_t		num_of_buttons;
}				t_pause_menu_handler;

bool			on_enter_pause_menu(void *param);
bool			on_leave_pause_menu(void *param);

bool			create_exit_button(t_env *env, t_game_pause *menu,
	t_pause_menu_handler *handler);

#endif
