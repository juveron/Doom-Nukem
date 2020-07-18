/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:17:12 by thboura           #+#    #+#             */
/*   Updated: 2020/07/14 22:09:52 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# include "doom_nukem.h"

/*
**	Editor inputs
*/

void	zoom_inputs(t_env *env);
void	basic_inputs(t_env *env, float dt);
bool	button_left_input(t_env *env);
void	button_right_input(t_env *env);
void	cancel_drag_input(t_env *env);
void	cancel_input(t_env *env);
bool	change_mode_input(t_env *env);
bool	delete_inputs(t_env *env);
void	display_gui_input(t_env *env);
bool	drag_map_point_input(t_env *env);
bool	game_input(t_env *env);
bool	global_editor_inputs(t_env *env);
bool	insert_input(t_env *env);
bool	line_input(t_env *env);
void	point_input(t_env *env);
bool	level_input(t_env *env);
bool	object_input(t_env *env);
int		pause_editor_inputs(t_env *env);
bool	save_map_input(t_env *env);
bool	set_history(t_env *env, t_history_window *history);
bool	undo_redo_input(t_env *env);
void	quit_input(t_env *env);

/*
**	Game inputs
*/

bool	game_over_inputs(t_env *env);
bool	global_game_inputs(t_env *env);
bool	global_game_editor_inputs(t_env *env);
int		pause_game_inputs(t_env *env);
void	player_inputs(t_env *env, float dt, t_vec3f *look_dir);
void	rotation_inputs(t_env *env, t_global_option *option);
void	rotation_game_inputs(t_env *env, t_global_option *option);

/*
**	Settings inputs
*/

bool	global_settings_inputs(t_env *env);
void	enable_fps_input(t_env *env);
void	hud_input(t_env *env);

/*
**	Main menu inputs
*/

bool	global_main_menu_inputs(t_env *env);

/*
**	Global move input
*/

bool	global_movement_ph_inputs(t_env *env, float dt);

void	update_rotation_start(t_env *env);

#endif
