/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:02:46 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 15:04:14 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	init_game_over_shortcuts(t_game_over_shortcuts *game_over)
{
	game_over->skip_animation = SDL_SCANCODE_SPACE;
}

static void	init_game_shortcuts(t_game_shortcuts *game)
{
	game->pause = SDL_SCANCODE_ESCAPE;
	set_default_user_inputs(&game->user);
}

static void	init_editor_shortcuts(t_editor_shortcuts *editor)
{
	editor->major.undo_redo = SDL_SCANCODE_Z;
	editor->major.cancel = SDL_SCANCODE_C;
	editor->major.save = SDL_SCANCODE_S;
	editor->modify.delete = SDL_SCANCODE_X;
	editor->modify.insert = SDL_SCANCODE_I;
	editor->movements.up = SDL_SCANCODE_UP;
	editor->movements.down = SDL_SCANCODE_DOWN;
	editor->movements.left = SDL_SCANCODE_LEFT;
	editor->movements.right = SDL_SCANCODE_RIGHT;
	editor->mouse_wheel.move = SDL_SCANCODE_LCTRL;
	editor->zoom.in = SDL_SCANCODE_EQUALS;
	editor->zoom.out = SDL_SCANCODE_MINUS;
	editor->grid.increase = SDL_SCANCODE_RIGHTBRACKET;
	editor->grid.decrease = SDL_SCANCODE_LEFTBRACKET;
	editor->level_point.start = SDL_SCANCODE_LCTRL;
	editor->level_point.end = SDL_SCANCODE_LSHIFT;
	editor->mode.level = SDL_SCANCODE_J;
	editor->mode.point = SDL_SCANCODE_P;
	editor->mode.line = SDL_SCANCODE_L;
	editor->mode.object = SDL_SCANCODE_O;
	editor->fps = SDL_SCANCODE_SPACE;
	editor->history = SDL_SCANCODE_H;
	editor->level_menu = SDL_SCANCODE_BACKSLASH;
	editor->game_state = SDL_SCANCODE_F5;
	init_editor_shortcut_p2(editor);
}

static void	init_menu_shortcuts(t_menu_shortcuts *menu)
{
	menu->quit = SDL_SCANCODE_ESCAPE;
	menu->up = SDL_SCANCODE_UP;
	menu->down = SDL_SCANCODE_DOWN;
	menu->validate = SDL_SCANCODE_RETURN;
}

void		init_shortcuts(t_shortcuts_inputs *shortcuts)
{
	shortcuts->system.quit = SDL_SCANCODE_ESCAPE;
	init_menu_shortcuts(&shortcuts->menu);
	init_editor_shortcuts(&shortcuts->editor);
	init_game_shortcuts(&shortcuts->game);
	init_game_over_shortcuts(&shortcuts->game_over);
}
