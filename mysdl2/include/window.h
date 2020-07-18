/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:21:56 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 22:36:49 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <SDL2/SDL.h>
# include "libft.h"
# include "clock.h"
# include "gui.h"

typedef struct s_container	t_container;

typedef struct				s_fps_counter
{
	t_u16		frames;
	t_clock		timer;
	t_u16		last_frame_count;
	SDL_Surface	*text;
	SDL_Surface *background;
}							t_fps_counter;

typedef struct				s_window
{
	SDL_Window		*handle;
	SDL_Surface		*surface;
	bool			is_focus;
	bool			is_close;
	bool			is_over;
	t_vec2i			pos;
	t_vec2i			size;
	int				id;
	char			*title;
	t_fps_counter	*fps_counter;
	t_container		*main_container;
	bool			need_redraw;
	bool			force_redraw;
}							t_window;

void						clear_window(t_window *win);
t_window					*create_window(char *title, t_vec2i pos,
	t_vec2i size, t_u32 flags);
bool						update_window(void);
bool						destroy_window(t_window *win);
t_window					*get_window_by_id(int win_id);
void						set_framerate(t_u32 framerate);
bool						is_over_window(t_window *win);

/*
**	FPS_counter.c
*/

int							enable_fps_counter(t_window *win);
void						disable_fps_counter(t_window *win);
bool						update_fps_counter(t_window *win);

#endif
