/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 10:58:48 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 15:37:04 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "libft.h"
# include <SDL2/SDL.h>

# define LEFT_BUTTON

typedef struct	s_key_event
{
	bool	key[SDL_NUM_SCANCODES];
	bool	last_key[SDL_NUM_SCANCODES];
}				t_key_event;

typedef struct	s_mouse_button
{
	bool	is_pressed;
	t_u8	clicks;
	t_vec2i	pos;
}				t_mouse_button;

typedef struct	s_mouse_button_event
{
	t_mouse_button	button[5];
	t_mouse_button	last_button[5];
}				t_mouse_button_event;

typedef struct	s_mouse_move_event
{
	t_vec2i	delta_pos;
	t_vec2i	pos;
	t_vec2i	global_pos;
}				t_mouse_move_event;

typedef struct	s_mouse_wheel_event
{
	t_s32	delta;
}				t_mouse_wheel_event;

typedef struct	s_position_event
{
	t_vec2i	pos;
}				t_position_event;

typedef struct	s_size_event
{
	t_vec2ui	size;
}				t_size_event;

typedef enum	e_window_event_type
{
	event_gained_focus,
	event_lost_focus,
	event_key_pressed,
	event_key_released,
	event_mouse_button_pressed,
	event_mouse_button_released,
	event_mouse_entered,
	event_mouse_left,
	event_mouse_moved,
	event_mouse_wheel_moved,
	event_moved,
	event_exposed,
	event_quit,
	event_resized
}				t_window_even_type;

typedef struct	s_textinput_event
{
	char	text[256];
}				t_textinput_event;

typedef struct	s_drop_event
{
	char	*file_name;
}				t_drop_event;

typedef struct	s_event
{
	t_u32					event_type;
	t_key_event				key;
	t_mouse_button_event	mouse_button;
	t_mouse_move_event		mouse_move;
	t_mouse_wheel_event		mouse_wheel;
	t_position_event		position;
	t_size_event			size;
	t_textinput_event		textinput;
	t_drop_event			drop;
}				t_event;

void			window_event(SDL_Event *event, t_event *handle_event);
void			handle_event(SDL_Event *event);

#endif
