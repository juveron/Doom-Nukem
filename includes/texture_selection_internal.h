/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_selection_internal.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 11:00:40 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 11:42:50 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_SELECTION_INTERNAL_H
# define TEXTURE_SELECTION_INTERNAL_H

# include "doom_nukem.h"

typedef struct	s_tex_sel
{
	SDL_Rect	rect;
	t_vec2f		uv;
	t_vec2f		step;
	SDL_Surface	*win;
	SDL_Surface	*surface;
	int			y;
}				t_tex_sel;

char			*get_right_name(char *path);
bool			update_texture_selection_func(void *param);
bool			draw_texture_selection_func(void *param);
void			scroll_texture(t_vec2i *mouse_pos,
		t_gui_texture_selection *selection);
#endif
