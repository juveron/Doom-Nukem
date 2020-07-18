/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_menu_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:00:11 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 19:53:18 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVELS_MENU_INTERNAL_H
# define LEVELS_MENU_INTERNAL_H

# include "doom_nukem.h"

bool	create_levels_label(t_levels_menu *levels_menu, t_env *env);

bool	create_levels_selection_change(t_levels_menu *levels_menu,
	t_env *env);

bool	create_move_up_button(t_levels_menu *levels_menu, t_env *env);
bool	create_move_down_button(t_levels_menu *levels_menu, t_env *env);

bool	create_scroll_up_button(t_levels_menu *levels_menu, t_env *env);
bool	create_scroll_down_button(t_levels_menu *levels_menu, t_env *env);

bool	create_new_map_button(t_levels_menu *levels_menu, t_env *env);

bool	load_levels(void *param);
bool	create_load_level_button(t_levels_menu *levels_menu, t_env *env);
bool	create_delete_level_button(t_levels_menu *levels_menu, t_env *env);

bool	create_map_name_label(t_levels_menu *levels_menu, t_env *env);
bool	create_map_name_textfield(t_levels_menu *levels_menu, t_env *env);

bool	create_file_name_label(t_levels_menu *levels_menu, t_env *env);
bool	create_file_name_textfield(t_levels_menu *levels_menu, t_env *env);

#endif
