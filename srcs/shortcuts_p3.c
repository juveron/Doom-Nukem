/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts_p2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:27:32 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 13:29:41 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	is_input_game_over_shortcut(t_game_over_shortcuts *game_over,
									SDL_Scancode input)
{
	return (input == game_over->skip_animation);
}

bool	is_input_game_shortcut(t_game_shortcuts *game, SDL_Scancode input)
{
	return (input == game->pause);
}

bool	is_input_editor_shortcut(t_editor_shortcuts *editor, SDL_Scancode input)
{
	return (input == editor->fps || input == editor->game_state
		|| input == editor->gravity || input == editor->grid.decrease
		|| input == editor->grid.increase || input == editor->history
		|| input == editor->level_menu || input == editor->level_point.end
		|| input == editor->level_point.start || input == editor->mode.level
		|| input == editor->mode.line || input == editor->mode.point
		|| input == editor->modify.delete || input == editor->modify.insert
		|| input == editor->movements.down || input == editor->movements.left
		|| input == editor->movements.right || input == editor->movements.up
		|| input == editor->texture || input == editor->zoom.in
		|| input == editor->zoom.out);
}

bool	is_input_menu_shortcut(t_menu_shortcuts *menu, SDL_Scancode input)
{
	return (input == menu->down || input == menu->quit || input == menu->up
			|| input == menu->validate);
}
