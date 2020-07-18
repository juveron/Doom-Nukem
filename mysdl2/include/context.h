/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:10:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 15:36:59 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include "clock.h"
# include "event.h"
# include "window.h"
# include "draw3d.h"

typedef struct	s_context
{
	t_map			*window;
	SDL_Event		event;
	bool			run;
	t_u32			framerate_limit;
	t_clock			timer;
	t_vec2i			mouse_pos;
	t_u8			*keys;
	SDL_Joystick	*joy;
	t_vec2i			axis;
	TTF_Font		*font;
	t_event			handle_event;
	t_vector		gui_trigger;
	t_window		*draw_window;
	t_context_3d	*context_3d;
}				t_context;

int				init_context(void);
bool			init_3d_context(void);
void			free_3d_context(void);
t_context		*get_context(void);
void			free_context(void);
t_u64			sdl_throw_error(char *msg, int ret_val, bool exit_val);
void			update_event(void);
bool			is_running(void);
SDL_Rect		rect(int x, int y, int w, int h);
bool			is_in_box(t_vec2i pos, SDL_Rect *rect);
bool			is_intersect(SDL_Rect *rect1, SDL_Rect *rect2);
void			blit_surface(SDL_Surface *surface, SDL_Rect rect,
								t_window *win);
void			set_color_background(t_u32 color, t_window *win);

#endif
