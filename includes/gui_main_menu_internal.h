/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main_menu_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:03:44 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 17:05:20 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_MAIN_MENU_INTERNAL_H
# define GUI_MAIN_MENU_INTERNAL_H

# include "doom_nukem.h"

bool	on_enter(void *param);
bool	on_leave(void *param);
bool	create_quit_button(t_main_menu *main_menu, t_env *env);
bool	create_settings_button(t_main_menu *main_menu, t_env *env);

#endif
