/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 22:26:30 by killian           #+#    #+#             */
/*   Updated: 2020/05/30 22:34:00 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "context.h"
# include "window.h"
# include "libft.h"

/*
**	input.c
*/

t_vec2i	get_mouse_position();
t_vec2i	get_mouse_position_delta();
bool	get_key(SDL_Scancode scancode);
bool	get_key_down(SDL_Scancode scancode);
bool	get_key_up(SDL_Scancode scancode);

/*
**	input_p2.c
*/

bool	get_button(int sdl_button, t_vec2i *pos);
bool	get_button_down(int sdl_button, t_vec2i *pos);
bool	get_button_up(int sdl_button, t_vec2i *pos);
t_s32	get_mouse_wheel(void);
t_u8	get_click(int sdl_button);

/*
**	input_p3.c
*/

char	*get_textinput(void);
t_vec2i	get_mouse_global_position(void);

#endif
