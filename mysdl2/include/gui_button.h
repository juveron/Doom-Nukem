/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:20:48 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:08:57 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_BUTTON_H
# define GUI_BUTTON_H

# include "SDL2/SDL.h"
# include "gui_trigger.h"
# include "window.h"

typedef struct	s_gui_button
{
	SDL_Rect		rect;
	t_window		*window;
	t_gui_trigger	*trigger;
	bool			is_select;
	SDL_Surface		*over;
	SDL_Surface		*not_over;
	void			(*on_select)(void *);
	void			*param;
}				t_gui_button;

t_gui_button	*create_gui_button(SDL_Rect rect, SDL_Surface *over,
	SDL_Surface *not_over, t_window *window);
void			set_gui_button_func(t_gui_button *button,
	void (*on_click)(void *), void *param);
void			delete_gui_button(t_gui_button **button);
void			draw_gui_button(t_gui_button *button);

#endif
