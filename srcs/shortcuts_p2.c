/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts_p2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 19:43:59 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 19:44:14 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_editor_shortcut_p2(t_editor_shortcuts *editor)
{
	editor->quit = SDL_SCANCODE_ESCAPE;
	editor->gravity = SDL_SCANCODE_K;
	editor->texture = SDL_SCANCODE_T;
}
