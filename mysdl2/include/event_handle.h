/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 12:04:28 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 22:19:57 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLE_H
# define EVENT_HANDLE_H

# include "libft.h"

typedef enum	e_event_type
{
	DEFAULT_EVENT_TYPE,
	CUSTOM_EVENT_TYPE
}				t_event_type;

typedef struct	s_event_handler
{
	t_dlist_handler *dlist_handler;
	t_event_type	event_type;
}				t_event_handler;

typedef struct	s_default_event
{
	bool	(*func)(void *);
	void	*param;
}				t_default_event;

typedef struct	s_custom_event
{
	bool	(*func)(void *, void *);
	void	*param;
}				t_custom_event;

typedef struct	s_event_vector
{
	t_event_handler	*event_handler;
	void			*param;
}				t_event_vector;

bool			trigger_gui_default_event(t_event_handler *event_handler);
bool			trigger_gui_custom_event(t_event_handler *event_handler,
		void *param);
bool			trigger_gui_event(void);
t_event_handler	*create_event_handler(t_event_type event_type);
bool			add_default_action(t_event_handler *event_handler,
	t_default_event *event);
bool			add_custom_action(t_event_handler *event_handler,
	t_custom_event *event);
void			remove_default_action(t_event_handler *event_handler,
	t_default_event *event);
void			remove_custom_action(t_event_handler *event_handler,
	t_custom_event *event);
bool			trigger_default_event(t_event_handler *event_handler);
bool			trigger_custom_event(t_event_handler *event_handler,
	void *param);
void			destroy_event_handler(t_event_handler *event_handler);

#endif
