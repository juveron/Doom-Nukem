/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:34:17 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 14:18:25 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "color.h"
# include <SDL2/SDL_ttf.h>
# include "clock.h"
# include "event_handle.h"

# define TOP_BAR_BUTTON_SIZE 10

typedef struct s_window		t_window;

typedef enum				e_gui_elem_type
{
	GUI_ELEM_MAIN_CONTAINER,
	GUI_ELEM_CUSTOM_WINDOW,
	GUI_ELEM_CONTAINER,
	GUI_ELEM_BUTTON,
	GUI_ELEM_CHECK_BOX,
	GUI_ELEM_LABEL,
	GUI_ELEM_TEXTFIELD,
	GUI_ELEM_CUSTOM
}							t_gui_elem_type;

typedef struct				s_component
{
	SDL_Rect			rect;
	SDL_Surface			*surface;
	t_gui_elem_type		elem_type;
	bool				use_background;
	t_color				background;
	SDL_Surface			*background_image;
	bool				is_visible;
	bool				need_redraw;
	char				*name;
	struct s_component	*parent;
	bool				(*draw)(void *);
	bool				(*update)(void *);
	bool				(*hide)(void *);
}							t_component;

/*
**	TODO: Add event to container like component_remove.
*/

typedef struct				s_container
{
	t_component	component;
	t_vector	array_component;
}							t_container;

typedef struct				s_gui_custom_window
{
	t_component		component;
	t_container		*container;
	bool			is_draggable;
	bool			is_dragged;
	t_vec2i			drag_offset;
	bool			is_over;
	SDL_Surface		*surface;
	t_event_handler	*on_window_move;
	t_event_handler	*on_window_close;
}							t_gui_custom_window;

typedef struct				s_gui_label
{
	t_component component;
	TTF_Font	*font;
	char		*name;
	t_color		color;
	SDL_Surface	*surface;
	bool		need_redraw;
}							t_gui_label;

typedef struct				s_gui_button
{
	t_component		component;
	t_gui_label		*label;
	bool			is_over;
	SDL_Surface		*image;
	t_event_handler	*on_click;
	t_event_handler	*on_enter;
	t_event_handler	*on_leave;
}							t_gui_button;

typedef struct				s_gui_textfield
{
	t_component		component;
	char			*default_text;
	t_color			text_color;
	t_u64			text_size_limit;
	char			*text;
	bool			need_redraw;
	SDL_Surface		*surface;
	TTF_Font		*font;
	t_event_handler	*on_text_change;
	bool			is_focus;
	t_u64			cursor_pos;
	t_u64			cursor_last_pos;
	t_u64			cursor_pos_coor;
	t_u64			text_size;
	t_clock			cursor_blink_timer;
	t_clock			backspace_timer;
	bool			cursor_visible;
}							t_gui_textfield;

typedef struct				s_gui_check_box
{
	t_component		component;
	bool			checked;
	t_event_handler	*on_toggle;
	t_color			color;
}							t_gui_check_box;

typedef struct				s_gui_fslider
{
	t_component			component;
	t_color				cursor_color;
	t_color				bar_color;
	SDL_Surface			*cursor_surface;
	SDL_Surface			*bar_surface;
	t_event_handler		*on_value_change;
	float				min_value;
	float				max_value;
	float				value;
	bool				is_clicked;
	int					pos;
	int					pixel_min;
	int					pixel_max;
	float				t;
}							t_gui_fslider;

bool						draw_component(t_component *component);

bool						init_main_container(t_window *window);
bool						update_gui(t_window *window);
bool						container_delete_index(t_container *container,
	size_t index);
bool						container_delete(t_container *container,
	t_component *component);
bool						container_add(t_container *container,
	void *component);
bool						container_add_index(t_container *container,
	t_component *component, int index);
t_container					*create_container(SDL_Rect	rect,
	bool use_background, t_color color);
bool						container_clear(t_container *container);
bool						destroy_container(t_container **container);

t_gui_custom_window			*create_custom_window(const SDL_Rect rect,
	const t_color color);
void						custom_window_set_draggable
	(t_gui_custom_window *custom_window, bool enable);

t_vec2i						get_component_pos(t_component *component);
t_container					*get_right_container(t_component *component);

t_gui_label					*create_label(const t_vec2i pos,
	const t_color color, TTF_Font *font, const t_color background_color);
bool						destroy_label(t_gui_label **label);
void						label_change_color(t_gui_label *label,
	const t_color color);
bool						label_change_name(t_gui_label *label,
	const char *name);

t_gui_button				*create_button(const SDL_Rect rect,
	const t_color color, TTF_Font *font);
bool						destroy_button(t_gui_button **button);
bool						button_change_name(t_gui_button *button,
	const char *name);

t_gui_textfield				*create_textfield(const SDL_Rect rect,
	const t_color color, TTF_Font *font);
bool						destroy_textfield(t_gui_textfield **textfield);
bool						textfield_change_default_text(
	t_gui_textfield *textfield, char *default_text);
bool						textfield_change_limit(t_gui_textfield *textfield,
	t_u64 limit);
bool						textfield_change_value(t_gui_textfield *textfield,
	char *value);

bool						destroy_custom_window(t_gui_custom_window **param);

bool						init_component(t_component *component,
	const SDL_Rect *rect, const bool use_background,
	const t_color color_background);
void						destroy_component(t_component *component);

bool						init_container(t_container *container,
	SDL_Rect	*rect, bool use_background, t_color color);
bool						draw_container(t_container *container);
bool						update_container(t_container *container);

void						set_visible(t_component *component,
	const bool enable);

t_gui_check_box				*create_check_box(const SDL_Rect rect,
	const t_color color);
bool						destroy_check_box(t_gui_check_box **param);
void						check_box_enable(t_gui_check_box *check_box,
	bool enable);

void						button_add_image(t_gui_button *button,
	SDL_Surface *surface);
void						button_remove_image(t_gui_button *button);
bool						check_button_is_over(t_gui_button *button);

t_gui_fslider				*create_fslider(const SDL_Rect rect,
	const float min, const float max);
void						fslider_change_bar_color(t_gui_fslider *slider,
	t_color color);
void						fslider_change_cursor_color(t_gui_fslider *slider,
	t_color color);
bool						destroy_fslider(t_gui_fslider **param);
float						fslider_get_value(t_gui_fslider *slider);
void						fslider_set_percent_value(t_gui_fslider *slider,
	float t);
void						fslider_set_value(t_gui_fslider *slider,
	float value);
bool						component_remove_from_parent(void *component);

void						component_change_background_color(void *component,
	bool use_background, t_color color);
void						component_add_background_image(void *component,
	SDL_Surface *surface);
void						component_remove_background_image(void *component);

#endif
