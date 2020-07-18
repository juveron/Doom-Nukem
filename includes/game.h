/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 03:44:48 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/15 02:15:30 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "doom_nukem.h"

t_game	*create_game_struct(void);
void	destroy_game_struct(t_game **game);
void	init_game_struct(t_game *game);
t_scene	*create_game_scene(t_env *env);
bool	update_game(void *param);
bool	draw_game(void *param);
void	update_win_menu(t_env *env);

#endif
