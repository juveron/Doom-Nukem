/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_trigger.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 08:11:17 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:08:57 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_TRIGGER_H
# define GUI_TRIGGER_H

# include <SDL2/SDL.h>
# include "libft.h"
# include "window.h"

typedef struct s_gui_trigger	t_gui_trigger;

typedef void	(*t_func_gui_trigger)(void *param);

typedef enum	e_gui_trig_func_type
{
	ENTER,
	LEAVE,
	STAY,
	CLICK,
	IDLE
}				t_gui_trig_func_type;

struct			s_gui_trigger
{
	SDL_Rect			rect;
	t_window			*window;
	bool				state;
	t_func_gui_trigger	on_enter;
	void				*on_enter_param;
	t_func_gui_trigger	on_leave;
	void				*on_leave_param;
	t_func_gui_trigger	stay;
	void				*stay_param;
	t_func_gui_trigger	on_click;
	void				*on_click_param;
	t_func_gui_trigger	idle;
	void				*idle_param;
};

t_gui_trigger	*create_gui_trigger(SDL_Rect rect, t_window *window);
void			set_gui_trigger_func(t_gui_trigger *trigger,
	t_gui_trig_func_type func_type, t_func_gui_trigger func, void *param);
void			update_gui_trigger(t_gui_trigger *trigger);
void			set_gui_trigger_active(t_gui_trigger *trigger, bool active);
void			delete_gui_trigger(t_gui_trigger **trigger);

#endif
