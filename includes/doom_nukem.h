/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:02:08 by thboura           #+#    #+#             */
/*   Updated: 2020/07/16 15:52:32 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "libft.h"
# include "mysdl2.h"
# include "mysndal.h"
# include "collider.h"
# include "physics.h"
# include "scene_manager.h"

# define WIDTH					1600
# define HEIGHT					800

# define PLAYER_HEIGHT			1.7f
# define CROUCH_HEIGHT			1.f

# define LEVEL_HEIGHT			1.f
# define PICKUP_HEIGHT			1.f

# define MAP_VERSION			"V1.4"

# define DEBUG_SELECTION_STATE	true

# if defined(__linux__)
#  define PREDEF_LINUX			true
# else
#  define PREDEF_LINUX			false
# endif

typedef struct s_env	t_env;
typedef t_u64			t_unique_id;

/*
**	t_portal_wall represent a wall with a sector behind him.
**
**	v1 -> index of first vertex
**	v2 -> index of second vertex
**	offset -> offset of the texture on the wall if is a full wall or upper part
**				of the wall if is portal wall and is visible
**	scale -> scale of the texture on the wall if is a full wall or upper part
**				of the wall if is portal wall and is visible
**	offsetl2 -> offset of the texture on the lower part of the wall if is
**				portal wall and is visible
**	scalel2 -> scale of the texture on the lower part of the wall if is portal
**				wall and is visible
**	nfloor -> i don't remember why i put this but it will come back to me xD
**	nceil -> i don't remember why i put this but it will come back to me xD
*/

typedef struct			s_objs_in_map
{
	SDL_Surface	*surface;
	size_t		remaining;
}						t_objs_in_map;

typedef struct			s_hud
{
	SDL_Surface		*heal;
	SDL_Rect		vec;
	t_clock			time;
	int				nb_heal;
	int				rend;
	t_objs_in_map	objs_in_map;
}						t_hud;

typedef	struct			s_compact_point
{
	t_u64		id;
	t_vertex	v;
	size_t		size;
	t_u64		*array;
}						t_compact_point;

typedef	struct			s_compact_vertices
{
	t_u64			max_id;
	size_t			size;
	t_compact_point	*array;
}						t_compact_vertices;

typedef	struct			s_point
{
	t_u64		id;
	t_vertex	v;
	t_map		*sector;
}						t_point;

typedef struct			s_sector_triangle
{
	t_point	*vertex[3];
}						t_sector_triangle;

typedef struct			s_sector_triangle_export
{
	t_unique_id	vertex_id[3];
	t_u64		index[3];
}						t_sector_triangle_export;

/*
**	t_sector represent a sector in map
**
**	floor -> height of the floor
**	ceil -> height of the ceil
**	walls -> dynamic array of walls in this sector
*/

typedef struct			s_aabb
{
	float	xmax;
	float	xmin;
	float	ymax;
	float	ymin;
}						t_aabb;

typedef struct			s_pvs
{
	t_vector	sector;
}						t_pvs;

typedef struct			s_sector
{
	t_u64		id;
	float		floor;
	float		ceil;
	t_vector	walls;
	t_vector	triangle_top;
	t_vector	triangle_bottom;
	t_aabb		aabb;
	bool		has_roof;
	t_material	*mtl_floor;
	t_material	*mtl_ceil;
	bool		floor_damage;
	t_pvs		pvs;
}						t_sector;

typedef enum			e_wall_location
{
	WALL_FULL = 0,
	WALL_TOP = 1 << 1,
	WALL_BOTTOM = 1 << 2,
	WALL_BOTH = 3,
	WALL_PORTAL = 1 << 4
}						t_wall_location;

typedef struct			s_ray
{
	t_vec3f	pos;
	t_vec3f	dir;
}						t_ray;

typedef struct			s_wall
{
	t_u64				sector_id;
	t_point				*v1;
	t_point				*v2;
	t_vec2f				offset;
	t_vec2f				scale;
	t_vec2f				offset2;
	t_vec2f				scale2;
	float				floor;
	float				ceil;
	t_sector			*neighbor;
	t_wall_location		wall_location;
	t_triangle			triangle[4];
	t_material			*mtl_top;
	t_material			*mtl_bottom;
}						t_wall;

typedef struct			s_player_spawn
{
	t_vec3f	pos;
	int		sector;
	float	angle;
}						t_player_spawn;

typedef enum			e_editor_global_state
{
	EDITOR_IDLE,
	EDITOR_MAKE_SECTOR
}						t_editor_global_state;

typedef enum			e_editor_selection_state
{
	EDITOR_SELECT_LINE = 1,
	EDITOR_SELECT_POINT,
	EDITOR_LEVELS,
	EDITOR_OBJECT
}						t_editor_selection_state;

typedef struct			s_editor_state
{
	t_editor_global_state		global_state;
	t_editor_selection_state	section_state;
}						t_editor_state;

typedef struct			s_notify
{
	bool		print_msg;
	bool		surface_init;
	SDL_Surface	*surface;
	t_clock		clock;
	char		*msg;
	t_color		color;
}						t_notify;

typedef struct			s_handler_struct
{
	t_sector	*sectors;
	t_wall		*walls;
	size_t		i;
	size_t		j;
	size_t		k;
}						t_handler_struct;

/*
**	Levels utils
*/

typedef struct			s_level_point
{
	t_vec3f		position;
	float		rotation;
	t_u64		sector_id;
	bool		available;
}						t_level_point;

typedef struct			s_move_handler
{
	bool			active;
	t_level_point	*dragged_point;
	t_level_point	saved_point;
}						t_move_handler;

typedef struct			s_level_edition
{
	bool			active;
	t_move_handler	move_handler;
}						t_level_edition;

typedef struct			s_level_param
{
	t_level_point	start;
	t_level_point	end;
}						t_level_param;

typedef struct			s_pickup_object
{
	t_vec3f		pos;
	t_u64		sector_id;
}						t_pickup_object;

typedef struct			s_doom_map
{
	t_unique_id		id;
	char			*name;
	t_map			*vertices;
	t_map			*sectors;
	t_vector		pickup_objects;
	t_level_param	level;
}						t_doom_map;

typedef struct			s_objects_manager
{
	bool			available;
	t_vector		remaining_object;
	t_texture		*texture;
	t_material		*material;
	t_event_handler	*on_pickedup_object;
}						t_objects_manager;

typedef struct			s_levels_manager
{
	t_level_edition		editor;
	SDL_Surface			*start_surface;
	SDL_Surface			*end_surface;
	t_texture			*end;
	t_texture			*start;
	t_material			*material_start;
	t_material			*material_end;
	t_render_object		*start_obj;
	t_render_object		*end_obj;
}						t_levels_manager;

typedef struct			s_level_handler_struct
{
	t_level_point	tmp_point;
	bool			is_start;
}						t_level_handler_struct;

/*
**	Deletion
*/

typedef struct			s_deletion
{
	t_u64		sector_id;
	t_u64		wall_index;
	t_wall		*wall1;
	t_wall		*wall2;
}						t_deletion;

/*
**	Insert utils
*/

typedef struct			s_neighbor_handler
{
	bool		active;
	t_wall		*wall;
	size_t		index;
}						t_neighbor_handler;

/*
**	Record utils
*/

typedef struct			s_recorded_event_func
{
	bool	(*undo)(t_env *env, void *);
	bool	(*redo)(t_env *env, void *);
	bool	(*delete)(void *);
}						t_recorded_event_func;

typedef struct			s_recorded_event_handler
{
	t_dlist_handler	*event_list;
	t_dlist			*current_event;
}						t_recorded_event_handler;

typedef enum			e_recorded_event_type
{
	REC_EVENT_ADD_POINT,
	REC_EVENT_INSERT_POINT,
	REC_EVENT_DEL_POINT,
	REC_EVENT_ADD_SECTOR,
	REC_EVENT_DEL_SECTOR,
	REC_EVENT_MOVE_POINT,
	REC_EVENT_ADD_START_LEVEL,
	REC_EVENT_ADD_END_LEVEL,
	REC_EVENT_MOVE_LEVEL_POINT,
	REC_EVENT_DEL_LEVEL_POINT,
	REC_EVENT_ADD_PICKUP,
	REC_EVENT_DEL_PICKUP
}						t_recorded_event_type;

typedef struct			s_rec_add_point_event
{
	t_recorded_event_func	func;
	t_point					*position;
}						t_rec_add_point_event;

typedef struct			s_rec_insert_point_event
{
	t_recorded_event_func	func;
	t_wall					*wall;
	t_point					*point;
	size_t					index;
	t_neighbor_handler		neighbor;
}						t_rec_insert_point_event;

typedef struct			s_rec_del_point_event
{
	t_recorded_event_func	func;
	t_vector				handler;
	t_point					*point;
}						t_rec_del_point_event;

typedef struct			s_rec_add_sector_event
{
	t_recorded_event_func	func;
	t_sector				*sector;
	t_vector				vertices;
}						t_rec_add_sector_event;

typedef struct			s_rec_del_sector_event
{
	t_recorded_event_func	func;
	t_sector				*sector;
	t_vector				vertices;
}						t_rec_del_sector_event;

typedef struct			s_rec_move_point_event
{
	t_recorded_event_func	func;
	t_u64					point;
	t_vec3f					last_pos;
	t_vec3f					current_pos;
}						t_rec_move_point_event;

typedef struct			s_rec_move_level_point_event
{
	t_recorded_event_func	func;
	t_level_point			old_point;
	t_level_point			new_point;
}						t_rec_move_level_point_event;

typedef struct			s_rec_del_level_point_event
{
	t_recorded_event_func	func;
	t_level_point			point;
	bool					is_start;
}						t_rec_del_level_point_event;

typedef struct			s_rec_level_event
{
	t_recorded_event_func	func;
	t_level_point			param;
	bool					is_start;
}						t_rec_level_event;

typedef struct			s_rec_add_pickup_event
{
	t_recorded_event_func	func;
	t_pickup_object			param;
}						t_rec_add_pickup_event;

typedef struct			s_rec_del_pickup_event
{
	t_recorded_event_func	func;
	t_vec3f					pos;
	size_t					sector_id;
	size_t					index;
}						t_rec_del_pickup_event;

typedef struct			s_recorded_event
{
	t_recorded_event_type	type;
	void					*param;
}						t_recorded_event;

typedef struct			s_drag_point
{
	t_point		*dragged_point;
	t_vertex	vertex;
	t_point		*point_selected;
	bool		point_is_dragged;
}						t_drag_point;

typedef struct			s_fonts
{
	TTF_Font	*deja_vu_sans_momo_16;
	TTF_Font	*deja_vu_sans_momo_30;
	TTF_Font	*deja_vu_sans_momo_60;
	TTF_Font	*covid_virus_120;
	TTF_Font	*badabb_120;
}						t_fonts;

typedef enum			e_app_state
{
	APP_MAIN_MENU,
	APP_EDITOR_GAME,
	APP_EDITOR,
	APP_SETTINGS,
	APP_GAME,
	APP_GAME_OVER,
	APP_WIN
}						t_app_state;

typedef struct			s_global_option
{
	float	mouse_sensibility;
}						t_global_option;

typedef struct			s_gui_input_button
{
	t_component		component;
	t_gui_label		*label;
	SDL_Surface		*image;
	t_event_handler	*on_click;
	t_env			*env;
}						t_gui_input_button;

typedef struct			s_gui_material_preview
{
	t_component	component;
	t_env		*env;
	SDL_Surface	*surface;
	t_material	*material;
	bool		need_redraw;
}						t_gui_material_preview;

typedef struct			s_image_export
{
	t_u32	*pixels;
	t_s32	w;
	t_s32	h;
}						t_image_export;

typedef struct			s_gui_texture_selection
{
	t_component				component;
	int						section_pos;
	int						start;
	t_texture				*array;
	size_t					array_size;
	t_env					*env;
	t_texture				*current_texture;
	t_material				*material;
	t_event_handler			*on_selection_change;
}						t_gui_texture_selection;

typedef struct			s_gui_levels_selection
{
	t_component		component;
	t_vector		*levels;
	t_u64			*current_map_index;
	t_u64			selected_index;
	t_u64			start;
	t_u64			end;
	t_u64			size;
	TTF_Font		*font;
	t_event_handler	*on_selection_change;
}						t_gui_levels_selection;

typedef struct			s_gui_event_selection
{
	t_component					component;
	t_recorded_event_handler	*event_handler;
	t_u64						selected_index;
	t_u64						start;
	t_u64						end;
	t_u64						size;
	TTF_Font					*font;
	t_env						*env;
}						t_gui_event_selection;

typedef struct			s_main_menu
{
	t_gui_button	*play_button;
	t_gui_button	*editor_button;
	t_gui_button	*quit_button;
	t_gui_button	*settings_button;
	t_container		*container;
}						t_main_menu;

typedef struct			s_selec_texture_menu
{
	t_gui_custom_window		*window;
	t_gui_label				*title;
	t_gui_material_preview	*preview;
	t_gui_texture_selection	*texture_selection;
	t_gui_label				*texture_id_info;
	t_gui_label				*texture_name_info;
	t_gui_button			*delete_button;
	t_container				*container;
}						t_selec_texure_menu;

typedef struct			s_material_menu
{
	t_env					*env;
	t_container				*container;
	bool					selec_texture_menu_open;
	t_material				*material;
	t_gui_label				*material_label;
	t_gui_label				*diffuse_color_label;
	t_gui_textfield			*diffuse_color_textfield;
	t_gui_label				*diffuse_texture_label;
	t_gui_button			*diffuse_texture_button;
	t_gui_label				*texture_pos_label;
	t_gui_label				*texture_pos_u_label;
	t_gui_textfield			*texture_pos_u_textfield;
	t_gui_label				*texture_pos_v_label;
	t_gui_textfield			*texture_pos_v_textfield;
	t_gui_label				*texture_scale_label;
	t_gui_label				*texture_scale_u_label;
	t_gui_textfield			*texture_scale_u_textfield;
	t_gui_label				*texture_scale_v_label;
	t_gui_textfield			*texture_scale_v_textfield;
	t_gui_label				*texture_rotation_label;
	t_gui_textfield			*texture_rotation_textfield;
	t_gui_button			*copy_button;
	t_gui_button			*past_button;
	t_gui_material_preview	*material_preview;
}						t_material_menu;

/*
**	/!\ NEED TO CHECK t_sector_menu->sector ON delete sector
**		IF IT'S NOT THE SELECTED SECTOR
*/

typedef struct			s_sector_menu
{
	t_container		*container;
	t_sector		*sector;
	t_env			*env;
	t_gui_label		*floor_level_label;
	t_gui_textfield	*floor_level_textfield;
	t_gui_label		*ceil_level_label;
	t_gui_textfield	*ceil_level_textfield;
	t_gui_label		*has_roof_label;
	t_gui_check_box	*has_roof_check_box;
	t_gui_label		*floor_damage_label;
	t_gui_check_box	*floor_damage_check_box;
}						t_sector_menu;

typedef struct			s_levels_menu
{
	t_env					*env;
	t_container				*container;
	t_render_object			*start_object;
	t_render_object			*end_object;
	t_doom_map				**current_map;
	t_gui_label				*levels_label;
	t_gui_levels_selection	*levels_selection;
	t_gui_button			*scroll_up_button;
	t_gui_button			*scroll_down_button;
	t_gui_button			*move_up_button;
	t_gui_button			*move_down_button;
	t_gui_button			*load_map_button;
	t_gui_button			*delete_map_button;
	t_gui_button			*new_map_button;
	t_gui_label				*map_name_label;
	t_gui_textfield			*map_name_textfield;
	t_gui_label				*file_name_label;
	t_gui_textfield			*file_name_textfield;
}						t_levels_menu;

typedef	struct			s_game_pause
{
	t_container		*container;
	size_t			is_over_button;
	t_gui_button	*resume_button;
	t_gui_button	*restart_button;
	t_gui_button	*settings_button;
	t_gui_button	*quit_button;
	t_gui_button	*exit_button;
}						t_game_pause;

typedef struct			s_pause_menu
{
	t_container		*container;
	size_t			is_over_button;
	t_gui_button	*resume_button;
	t_gui_button	*edit_button;
	t_gui_button	*settings_button;
	t_gui_button	*quit_button;
}						t_pause_menu;

typedef struct			s_history_window
{
	bool					available;
	t_window				*window;
	t_gui_event_selection	*event_selection;
}						t_history_window;

typedef enum			e_gui_status
{
	GUI_NONE,
	GUI_WALL,
	GUI_SECTOR,
	GUI_LEVELS,
	GUI_PAUSE,
	GUI_SETTINGS,
	GUI_INPUT,
	GUI_MAIN_MENU,
	GUI_GAME_OVER,
	GUI_WIN
}						t_gui_status;

typedef struct			s_input_display
{
	t_container		*container;
	t_gui_label		*label;
}						t_input_display;

typedef struct			s_input_handler
{
	t_gui_status	previous_state;
	SDL_Scancode	input_scancode;
	bool			(*set_input_func)(t_env *env, SDL_Scancode input_scancode);
	t_input_display	display;
}						t_input_handler;

typedef struct			s_ambient_options
{
	t_gui_label		*ambient_amplitude_label;
	t_gui_fslider	*ambient_amplitude_fslider;
	t_gui_label		*ambient_music_amplitude_label;
	t_gui_fslider	*ambient_music_amplitude_fslider;
	t_gui_label		*game_over_music_amplitude_label;
	t_gui_fslider	*game_over_music_amplitude_fslider;
}						t_ambient_options;

typedef struct			s_gui_options
{
	t_gui_label		*gui_amplitude_label;
	t_gui_fslider	*gui_amplitude_fslider;
	t_gui_label		*open_pause_amplitude_label;
	t_gui_fslider	*open_pause_amplitude_fslider;
	t_gui_label		*close_pause_amplitude_label;
	t_gui_fslider	*close_pause_amplitude_fslider;
	t_gui_label		*select_button_amplitude_label;
	t_gui_fslider	*select_button_amplitude_fslider;
}						t_gui_options;

typedef struct			s_objects_options
{
	t_gui_label		*objects_amplitude_label;
	t_gui_fslider	*objects_amplitude_fslider;
	t_gui_label		*start_of_level_amplitude_label;
	t_gui_fslider	*start_of_level_amplitude_fslider;
	t_gui_label		*end_of_level_amplitude_label;
	t_gui_fslider	*end_of_level_amplitude_fslider;
}						t_objects_options;

typedef struct			s_audio_options
{
	t_container			*container;
	t_gui_label			*global_amplitude_label;
	t_gui_fslider		*global_amplitude_fslider;
	t_ambient_options	ambient;
	t_gui_options		gui;
	t_objects_options	objects;
}						t_audio_options;

typedef struct			s_user_inputs
{
	SDL_Scancode	move_forward;
	SDL_Scancode	move_back;
	SDL_Scancode	move_left;
	SDL_Scancode	move_right;
	SDL_Scancode	move_up;
	SDL_Scancode	move_down;
	SDL_Scancode	jump;
	SDL_Scancode	sprint;
	SDL_Scancode	crouch;
}						t_user_inputs;

typedef struct			s_controls_options
{
	t_container			*container;
	t_gui_label			*move_forward_label;
	t_gui_input_button	*move_forward_button;
	t_gui_label			*move_back_label;
	t_gui_input_button	*move_back_button;
	t_gui_label			*move_left_label;
	t_gui_input_button	*move_left_button;
	t_gui_label			*move_right_label;
	t_gui_input_button	*move_right_button;
	t_gui_label			*move_up_label;
	t_gui_input_button	*move_up_button;
	t_gui_label			*move_down_label;
	t_gui_input_button	*move_down_button;
	t_gui_label			*jump_label;
	t_gui_input_button	*jump_button;
	t_gui_label			*sprint_label;
	t_gui_input_button	*sprint_button;
	t_gui_label			*crouch_label;
	t_gui_input_button	*crouch_button;
}						t_controls_options;

typedef struct			s_other_options
{
	t_container		*container;
	t_gui_label		*skybox_label;
	t_gui_check_box	*skybox_check_box;
	t_gui_label		*debug_triangles_label;
	t_gui_check_box	*debug_triangles_check_box;
	t_gui_label		*fps_label;
	t_gui_check_box	*fps_check_box;
	t_gui_label		*game_over_animation_label;
	t_gui_check_box	*game_over_animation_check_box;
}						t_other_options;

typedef enum			e_settings_options
{
	AUDIO_OPTION,
	OTHER_OPTION,
	CONTROLS_OPTION,
	NUM_OF_OPTIONS
}						t_settings_options;

typedef struct			s_settings_menu
{
	t_container			*container;
	t_gui_status		prev_gui_status;
	t_app_state			prev_app_state;
	t_gui_button		*resume_button;
	t_gui_button		*exit_button;
	t_settings_options	current_option;
	t_gui_button		*audio_button;
	t_audio_options		audio;
	t_gui_button		*other_button;
	t_other_options		other;
	t_gui_button		*controls_button;
	t_controls_options	controls;
}						t_settings_menu;

typedef struct			s_game_over_menu
{
	t_container		*container;
	t_gui_label		*game_over_label;
	t_gui_button	*restart_button;
	t_gui_button	*main_menu_button;
	t_gui_button	*exit_button;
}						t_game_over_menu;

typedef struct			s_win_menu
{
	t_container		*container;
	t_gui_label		*win_label;
	t_gui_button	*restart_button;
	t_gui_button	*main_menu_button;
	t_gui_button	*exit_button;
	float			current_time;
	float			animation_time;
	bool			animation;
	t_gui_label		*time_label;
	t_gui_label		*highscore_label;
}						t_win_menu;

typedef struct			s_gui
{
	t_gui_status		status;
	t_input_handler		input_handler;
	t_game_over_menu	game_over_menu;
	t_win_menu			win_menu;
	t_settings_menu		settings_menu;
	t_pause_menu		pause_menu;
	t_game_pause		game_pause_menu;
	t_sector_menu		sector_menu;
	t_gui_custom_window	*window;
	t_material_menu		*material_menu;
	t_levels_menu		levels_menu;
	t_gui_custom_window	*texture_window;
	t_selec_texure_menu	*texture_menu;
	t_main_menu			main_menu;
}						t_gui;

typedef enum			e_selection_type
{
	SELEC_NONE,
	SELEC_WALL,
	SELEC_FLOOR,
	SELEC_CEIL
}						t_selection_type;

typedef struct			s_wall_selection
{
	t_wall			*wall;
	t_sector		*sector;
	t_wall_location	location;
}						t_wall_selection;

typedef union			u_selection_data
{
	t_wall_selection	wall;
	t_sector			*sector;
}						t_selection_data;

typedef struct			s_selection
{
	t_selection_type	type;
	t_selection_data	data;
}						t_selection;

typedef struct			s_images_gui
{
	SDL_Surface	*up_arrow_30x30;
	SDL_Surface	*down_arrow_30x30;
	SDL_Surface	*plus_30x30;
	SDL_Surface	*button_background_1;
}						t_images_gui;

typedef struct			s_global_mesh
{
	t_mesh	*cube_mesh;
	t_mesh	*fragment_mesh;
	t_mesh	*skybox_mesh;
}						t_global_mesh;

/*
**	source types must respect this order:
**		- objects ;
**		- gui ;
**		- ambient.
*/

typedef enum			e_source_type
{
	START_OF_LEVEL,
	END_OF_LEVEL,
	OPEN_PAUSE,
	CLOSE_PAUSE,
	SELECT_BUTTON,
	AMBIENT_MUSIC,
	GAME_OVER_MUSIC,
	NUM_OF_SOURCES
}						t_source_type;

/*
** source amplitude is calculated as such :
**		amplitude = sound_amplitude * class_amplitude * global_amplitude
*/

typedef struct			s_audio_output
{
	bool	available;
	ALuint	source;
	float	amplitude;
}						t_audio_output;

/*
**	sound classes
*/

typedef struct			s_objects_sounds
{
	float			amplitude;
	t_audio_output	start_of_level;
	t_audio_output	end_of_level;
}						t_objects_sounds;

typedef struct			s_gui_sounds
{
	float			amplitude;
	t_audio_output	open_pause_menu;
	t_audio_output	close_pause_menu;
	t_audio_output	select_button;
}						t_gui_sounds;

typedef struct			s_ambient_sounds
{
	float			amplitude;
	t_audio_output	ambient_music;
	t_audio_output	game_over_music;
}						t_ambient_sounds;

typedef enum			e_audio_class
{
	AMBIENT_CLASS,
	GUI_CLASS,
	OBJECTS_CLASS
}						t_audio_class;

typedef struct			s_sound_manager
{
	bool				available;
	t_default_master	*master;
	float				global_amplitude;
	t_objects_sounds	audio_objects;
	t_gui_sounds		audio_gui;
	t_ambient_sounds	audio_ambient;
}						t_sound_manager;

typedef struct			s_copy_material
{
	t_material	*material;
}						t_copy_material;

typedef struct			s_editor
{
	t_drag_point				drag_point;
	t_notify					notify;
	t_vertex					position_map;
	float						subdiv;
	int							div;
	t_vec2f						begin;
	t_wall						*closest;
	t_editor_state				state;
	t_vector					tmp_vertices;
	t_sector					*tmp_sector;
	t_player_spawn				player_spawn;
	int							current_sector;
	t_recorded_event_handler	event_handler;
	t_history_window			history;
	t_u64						unique_id_vertices;
	t_u64						unique_id_sectors;
	t_vec2f						offset;
	t_vec2f						offset_z;
	float						zoom;
	t_selection					selection;
	t_vec3f						last_map_pos;
	t_copy_material				copy;
}						t_editor;

typedef enum			e_state
{
	ST_ON_GROUND,
	ST_CROUCH
}						t_state;

typedef struct			s_player
{
	t_physics_component	physic;
	t_transform			*transform;
	t_vec3f				new_pos;
	t_u64				state;
	bool				speed;
	float				height;
}						t_player;

typedef struct			s_game_over_shortcuts
{
	SDL_Scancode	skip_animation;
}						t_game_over_shortcuts;

typedef struct			s_game_shortcuts
{
	SDL_Scancode	pause;
	t_user_inputs	user;
}						t_game_shortcuts;

typedef struct			s_editor_mode
{
	SDL_Scancode	level;
	SDL_Scancode	point;
	SDL_Scancode	line;
	SDL_Scancode	object;
}						t_editor_mode;

typedef struct			s_editor_level_point
{
	SDL_Scancode	start;
	SDL_Scancode	end;
}						t_editor_level_point;

typedef struct			s_editor_grid
{
	SDL_Scancode	increase;
	SDL_Scancode	decrease;
}						t_editor_grid;

typedef struct			s_editor_zoom
{
	SDL_Scancode	in;
	SDL_Scancode	out;
}						t_editor_zoom;

/*
**	- basic mouse wheel input zooms.
**	- move basic input moves horizontally.
**		alternate input (with SDL_SCANCODE_LALT) moves vertically.
*/

typedef struct			s_editor_wheel_input
{
	SDL_Scancode	move;
}						t_editor_wheel_input;

typedef struct			s_editor_movements
{
	SDL_Scancode	up;
	SDL_Scancode	down;
	SDL_Scancode	left;
	SDL_Scancode	right;
}						t_editor_movements;

typedef struct			s_modify_edition
{
	SDL_Scancode	delete;
	SDL_Scancode	insert;
}						t_modify_edition;

typedef struct			s_major_edition
{
	SDL_Scancode	undo_redo;
	SDL_Scancode	cancel;
	SDL_Scancode	save;
}						t_major_edition;

typedef struct			s_editor_shortcuts
{
	t_major_edition			major;
	t_modify_edition		modify;
	t_editor_movements		movements;
	t_editor_wheel_input	mouse_wheel;
	t_editor_zoom			zoom;
	t_editor_grid			grid;
	t_editor_level_point	level_point;
	t_editor_mode			mode;
	SDL_Scancode			fps;
	SDL_Scancode			history;
	SDL_Scancode			level_menu;
	SDL_Scancode			game_state;
	SDL_Scancode			quit;
	SDL_Scancode			gravity;
	SDL_Scancode			texture;
}						t_editor_shortcuts;

typedef struct			s_menu_shortcuts
{
	SDL_Scancode	quit;
	SDL_Scancode	up;
	SDL_Scancode	down;
	SDL_Scancode	validate;
}						t_menu_shortcuts;

/*
**	system and major_* shortcuts always need combination with SDL_SCANCODE_LCTRL
*/

typedef struct			s_system_shortcuts
{
	SDL_Scancode	quit;
}						t_system_shortcuts;

typedef struct			s_shortcuts_inputs
{
	t_system_shortcuts		system;
	t_menu_shortcuts		menu;
	t_editor_shortcuts		editor;
	t_game_shortcuts		game;
	t_game_over_shortcuts	game_over;
}						t_shortcuts_inputs;

typedef struct			s_map_file
{
	char *file_name;
}						t_map_file;

typedef struct			s_game_scene
{
	t_scene	*main_menu;
	t_scene	*game;
	t_scene	*editor;
}						t_game_scene;

typedef struct			s_game
{
	t_sector	*current_sector;
	t_vector	visible_sector;
	t_u64		current_segment_time;
	t_u64		highscore;
}						t_game;

typedef struct			s_game_over_animation
{
	t_clock		time;
	float		bright_ratio;
}						t_game_over_animation;

typedef struct			s_game_over
{
	bool					active;
	t_game_over_animation	animation;
}						t_game_over;

struct					s_env
{
	t_app_state			app_state;
	t_game_scene		scenes;
	t_game				*game;
	t_player			player;
	t_ph_context		ph_context;
	bool				use_gravity;
	float				time_scale;
	t_vector			maps;
	t_map_file			map_file;
	t_images_gui		gui_image;
	t_global_mesh		global_mesh;
	bool				sky_enable;
	t_render_object		*skybox;
	t_texture			*skybox_texture;
	t_global_option		global_option;
	t_fonts				fonts;
	SDL_Surface			*global_state;
	SDL_Surface			*selection_state;
	t_doom_map			*current_map;
	t_hud				hud;
	t_u64				current_map_index;
	t_editor			editor;
	t_window			*main_window;
	t_window			*map_window;
	bool				test_mode;
	float				wall;
	float				a;
	float				dt;
	int					tmp;
	char				buff[256];
	float				z;
	float				w;
	t_camera			camera;
	t_gui				gui;
	t_map				*texture_array;
	t_u64				texture_unique_id;
	t_levels_manager	levels_manager;
	t_objects_manager	objects_manager;
	t_sound_manager		sound_manager;
	t_shortcuts_inputs	shortcuts;
	t_game_over			game_over;
	bool				need_redraw;
	SDL_Surface			*framebuffer;
};

/*
**	env.c
*/

t_env					*init_env(void);
t_env					*free_env(t_env *env);

/*
**	error.c
*/

void					throw_error(char *msg, t_env *env);
void					exit_doom(t_env *env);

/*
**	app.c
*/

int						app_run(char **av);

/*
**	read_map.c
*/

bool					load_map(char *path, t_env *env);
void					unload_map(t_env *env);

bool					change_selection_mode(t_env *env,
	t_editor_selection_state state);
void					convert_tmp_sector(t_env *env);
bool					add_point_tmp(t_env *env);
int						delete_point(t_env *env, t_point *point, bool record);
void					delete_sector2(t_env *env, size_t index);
t_u64					delete_sector(t_sector *sector, t_env *env);

void					send_notify(char *msg, t_color color, t_env *env);
bool					draw_notify(t_env *env);
void					update_notify(t_env *env, t_notify *notify);
void					destroy_notify(t_env *env);

bool					export_map_file(char *pathfile, t_env *env);
bool					import_maps(char *pathfile, t_env *env);

bool					inside(t_vec2f *pos, t_sector *sector, bool edge);
int						clockwise_dir(t_sector *sector);

t_u32					get_dragged_point(t_env *env);
void					drag_point(t_point *point, t_vertex *new_pos);

bool					triangulate_sector(t_sector *sector);

t_gui_material_preview	*create_material_preview(SDL_Rect rect, t_env *env);
bool					destroy_material_preview(
	t_gui_material_preview **mat_prev);
void					material_preview_change_material(
	t_gui_material_preview *mat_prev, t_material *mat);

t_gui_texture_selection	*create_texture_selection(SDL_Rect rect, t_env *env);

bool					destroy_texture_selection(
	t_gui_texture_selection **selec);
bool					destroy_levels_selection(
	t_gui_levels_selection **levels_selec);
bool					destroy_level_menu(t_levels_menu *levels_menu);

/*
**	events
*/

bool					init_event_handler(t_recorded_event_handler \
	*event_handler);
void					free_event_handler(t_recorded_event_handler \
	*event_handler);
bool					record_event(t_env *env, t_recorded_event_type \
	event_type, void *param);
bool					undo_event(t_recorded_event_handler *event_handler,
	t_env *env);
bool					redo_event(t_recorded_event_handler *event_handler,
	t_env *env);
void					display_events(t_env *env, int new_elems);
char					*get_event_type(t_recorded_event_type type);

bool					add_sector_event(t_env *env);
bool					add_point_event(t_env *env,
	t_point *position);
bool					delete_point_event(t_env *env, t_vector *handler,
	t_point *point);
bool					cancel_point_deletion(t_env *env, t_deletion *handler,
	size_t total);
bool					move_point_event(t_env *env, t_point *point,
	t_vec3f new_pos, t_vec3f old_pos);
bool					delete_sector_event(t_env *env, t_sector *sector);
void					cancel_sector_record(t_env *env);
bool					add_level_point_event(t_env *env, bool is_start);
bool					move_level_point_event(t_env *env,
	t_level_point *old_point, t_level_point *new_point);
bool					delete_level_point_event(t_env *env,
	t_level_point *point, bool is_start);
bool					insert_point_event(t_env *env, t_wall *wall,
	size_t index, t_neighbor_handler *neighbor);
bool					add_pickup_object_event(t_env *env,
	t_pickup_object *pickup_object);
bool					delete_pickup_object_event(t_env *env,
	t_vec3f *pos, size_t sector_id, size_t index);

/*
**	levels
*/

bool					init_levels_manager(t_env *env,
	t_levels_manager *levels_manager);
bool					init_levels_manager_3d(t_env *env);
void					load_level_position(t_env *env);
void					free_levels_manager_3d(t_env *env);

void					free_levels_manager(t_env *env);
void					add_level_surface(t_levels_manager *levels_manager,
	TTF_Font *font);
bool					add_level_point(t_env *env, t_vec3f *position,
	bool is_start, bool record);
bool					add_start(t_env *env, t_vec3f *position,
	t_sector *sector);
bool					add_end(t_env *env, t_vec3f *position,
	t_sector *sector);
void					update_level_surfaces(t_env *env,
	t_levels_manager *levels_manager);
bool					check_if_already_exists(t_env *env, t_vec3f *position);
bool					check_if_other_exists(t_env *env, t_level_point *point);
t_dlist					*get_level_by_id(t_levels_manager *levels_manager,
	size_t id);
t_level_point			*get_level_point(t_level_param *level_param,
	t_vec3f *position);
void					move_level_point(t_env *env, t_move_handler *handler);
bool					check_moved_point(t_env *env, t_move_handler *handler);
void					revert_level_start_end(t_levels_manager *levels_manager,
	t_dlist *level);
bool					delete_level_point(t_env *env,
	t_level_point *point, bool record);
int						highlight_size(t_vec4f mouse_pos, t_level_param *param);
void					draw_gui_level(t_env *env);
void					remove_last_surface(t_levels_manager *levels_manager);
void					update_levels_id(t_dlist *level, bool increase);
bool					verify_sector_level_points(t_env *env, t_point *point);
bool					verify_sector_in_levels(t_env *env, t_sector *sector);
bool					update_level(t_env *env, float dt);
bool					point_remove_sector(t_point *point, t_sector *sector);
bool					set_current_map_by_index(t_env *env, t_u64 index);

/*
**	usefull fonctions to classify
*/

bool					set_game_start(t_env *env);

void					free_selection_mode(t_env *env);

t_point					*point_clone(t_point *point);
void					point_free(t_point *point);

bool					tmp_sector_clone(t_vector *new_vertices,
	t_vector *new_walls, t_vector *tmp_vertices, t_vector *tmp_wall);

void					remove_neighbor(t_sector *sector, t_sector *neighbor);

t_sector				*is_in_sector(t_env *env, t_vec2f *pos, bool edge);

t_sector				*sector_clone(t_sector *sector, t_vector *vertices);

bool					point_add_sector(t_point *point, t_sector *sector);
t_point					*add_vertex(t_point *v, t_env *env);
t_u64					get_correct_index(t_u64 n, t_s64 di);

bool					convert_sector(t_sector *sector, t_vector *vertices,
	t_env *env);
bool					set_vertex_sector(t_sector *sector, t_env *env);

bool					init_3d(t_env *env);

void					update_sector_aabb(t_sector *sector);
bool					print_hud(t_env *env);
void					init_hud(t_env *env);
bool					create_hud(t_env *env);
bool					hud_off_on(t_env *env);
bool					update_damage(t_env *env);
bool					blit_clock(t_env *env);
bool					blit_objects(t_env *env, t_objs_in_map *objs);
void					destroy_hud(t_env *env);

void					free_sector_event(t_sector *sector, t_vector *vertices);
bool					create_sector_menu(t_sector_menu *sector_menu,
	t_env *env);

t_wall					*wall_clone(t_wall *wall);
void					free_wall(t_wall *wall);
void					free_wall_event(t_wall *wall);
void					free_walls_sector(t_vector *walls_vector);
void					free_sector(t_sector *sector);

bool					insert_point(t_env *env, t_point *point, t_wall *wall,
	t_rec_insert_point_event *tmp);
bool					recorded_insert_point(t_env *env);
t_vec2f					win_to_map(t_vec2i *win_pos, t_env *env);
bool					update_input(t_env *env);
void					zoom(t_vec2i pos, t_env *env, float z);
bool					check_multiple_points(t_env *env);
void					free_tmp_vertices(t_env *env);
void					free_tmp_sector(t_env *env);
bool					is_over_gui_window(t_env *env);
bool					remap_point_id(t_point *point, t_env *env);
t_wall					*get_wall_by_position(t_wall *closest,
	t_sector *sector, size_t *index);

bool					destroy_input_display(t_env *env,
	t_input_display *display);
bool					create_input_display(t_env *env,
	t_input_display *display);
bool					init_input_event(void *env, void *set_input_func);

/*
**	texture_menu.c
*/

t_material_menu			*create_texture_menu(t_component *parent, t_env *env);
bool					init_texture_menu(t_material_menu *texture_menu,
	t_material *material);

void					flip_wall(t_sector *sector, t_env *env);
t_selec_texure_menu		*create_selec_texture_menu(t_env *env);
bool					init_sector_menu(t_sector_menu *menu, t_sector *sector,
	bool floor, t_env *env);
bool					init_wall_menu(t_wall *wall, bool top,
	t_env *env);
bool					set_material(t_sector *sector);
bool					triangulate_all_neighbor(t_sector *sector);

void					init_maps(t_env *env);
void					free_maps(t_env *env);
void					init_levels_menu(t_levels_menu *levels_menu,
	t_env *env);
bool					create_levels_menu(t_levels_menu *levels_menu,
	t_env *env);
t_gui_levels_selection	*create_levels_selection(SDL_Rect rect,
	t_vector *levels, t_env *env);

void					load_image_for_gui(t_env *env);
void					free_image_for_gui(t_env *env);
t_doom_map				*create_map(char *name);
void					remap_neighbor(t_sector *sector, t_env *env);

bool					load_global_mesh(t_env *env);
bool					check_collision(t_env *env, float dt);

void					free_map(t_doom_map	*map);

/*
**	print_debug.c
*/

void					print_grid_debug(t_env *env);
void					print_snap_point_debug(t_env *env);
void					print_global_state_debug(t_env *env);
void					print_point_selected_debug(t_env *env);

/*
**	settings_menu
*/

bool					destroy_settings_menu(t_settings_menu *menu);
void					disable_current_option(t_settings_menu *menu);
bool					create_settings_menu(t_env *env, t_settings_menu *menu);
bool					create_settings_menu_p2(t_env *env,
	t_settings_menu *menu);
void					init_settings_menu(t_env *env);
bool					resume_settings_menu(void *param);
bool					exit_settings_menu(void *param);

bool					destroy_ambient_options(t_ambient_options *ambient);
bool					create_ambient_options(t_env *env,
	t_ambient_options *ambient, SDL_Rect box, size_t num_of_buttons);

bool					destroy_gui_options(t_gui_options *gui);
bool					create_gui_options(t_env *env, t_gui_options *gui,
	SDL_Rect box, size_t num_of_buttons);

bool					destroy_objects_options(t_objects_options *objects);
bool					create_objects_options(t_env *env,
	t_objects_options *objects, SDL_Rect box, size_t num_of_buttons);

bool					destroy_audio_options(t_audio_options *audio);
bool					create_audio_options(t_env *env,
	t_audio_options *audio);
bool					init_audio_options(void *param);

bool					destroy_controls_options(t_controls_options *controls);
bool					create_controls_options(t_env *env,
	t_controls_options *controls);
bool					create_controls_options_p2(t_env *env,
	t_controls_options *controls, SDL_Rect button_template);
bool					create_controls_options_p7(t_env *env,
	t_controls_options *controls, SDL_Rect button_template);
bool					init_controls_options(void *param);
const char				*get_used_key_string(SDL_Scancode scancode);
bool					reset_control_key(t_env *env,
	t_gui_input_button *button, SDL_Scancode *key_address,
	SDL_Scancode new_scancode);
bool					change_move_forward_key(t_env *env,
	SDL_Scancode input_scancode);
bool					change_move_back_key(t_env *env,
	SDL_Scancode input_scancode);
bool					change_move_left_key(t_env *env,
	SDL_Scancode input_scancode);
bool					change_move_right_key(t_env *env,
	SDL_Scancode input_scancode);
bool					change_move_up_key(t_env *env,
	SDL_Scancode input_scancode);
bool					change_move_down_key(t_env *env,
	SDL_Scancode input_scancode);
bool					change_jump_key(t_env *env,
	SDL_Scancode input_scancode);
bool					change_sprint_key(t_env *env,
	SDL_Scancode input_scancode);
bool					change_crouch_key(t_env *env,
	SDL_Scancode input_scancode);

bool					destroy_other_options(t_other_options *test);
bool					create_other_options(t_env *env, t_other_options *test);
bool					create_other_options_p2(t_env *env,
	t_other_options *test, SDL_Rect option_template);
bool					init_other_options(void *param);
bool					disable_skybox(void *text, void *param);
bool					enable_debug_triangles(void *text, void *param);
bool					enable_fps(void *text, void *param);
bool					enable_animation(void *text, void *param);
void					verify_other_check_boxes(t_env *env,
	t_other_options *other);

/*
**	pause_menu
*/

bool					update_pause_menu(t_env *env, t_pause_menu *menu);
bool					destroy_pause_menu(t_pause_menu *menu);
bool					create_pause_menu(t_env *env, t_pause_menu *menu);
void					init_pause_menu(t_env *env);
bool					resume_pause_menu(void *param);
bool					edit_pause_menu(void *param);
bool					settings_pause_menu(void *param);
bool					quit_pause_menu(void *param);

/*
**	game_pause_menu
*/

bool					update_game_pause(t_env *env, t_game_pause *menu);
bool					destroy_game_pause(t_game_pause *menu);
bool					create_game_pause_menu(t_env *env, t_game_pause *menu);
void					init_game_pause(t_env *env);
bool					resume_game_pause(void *param);
bool					restart_game_pause(void *param);
bool					quit_game_pause(void *param);
bool					exit_game_pause(void *param);

/*
**	event window
*/

void					reset_history_window_pos(t_env *env,
	t_window *history_window);
bool					init_history(t_env *env, t_history_window *history);
bool					destroy_history(t_history_window *history);

/*
**	sounds
*/

bool					init_sound_manager(t_sound_manager *manager);
bool					destroy_sound_manager(t_sound_manager *manager);

bool					delete_audio(t_audio_output *audio);
bool					update_audio_source_amplitude(t_sound_manager *manager,
	t_audio_output *audio, float class_amplitude, float new_amplitude);
bool					create_audio(t_audio_output *audio,
	t_sound_manager *manager, size_t buffer_id);

bool					destroy_ambient(t_ambient_sounds *audio_ambient);
bool					create_ambient_music(t_sound_manager *manager,
	t_audio_output *ambient_music);
bool					create_game_over_music(t_sound_manager *manager,
	t_audio_output *game_over_music);
bool					init_ambient(t_sound_manager *manager,
	t_ambient_sounds *audio_ambient);

bool					destroy_gui(t_gui_sounds *audio_gui);
bool					create_open_pause_menu(t_sound_manager *manager,
	t_audio_output *open_pause_menu);
bool					create_close_pause_menu(t_sound_manager *manager,
	t_audio_output *close_pause_menu);
bool					create_select_button(t_sound_manager *manager,
	t_audio_output *select_button);
bool					init_gui(t_sound_manager *manager,
	t_gui_sounds *audio_gui);

bool					destroy_objects(t_objects_sounds *audio_objects);
bool					create_start_of_level(t_sound_manager *manager,
	t_audio_output *start_of_level);
bool					create_end_of_level(t_sound_manager *manager,
	t_audio_output *end_of_level);
bool					init_objects(t_sound_manager *manager,
	t_objects_sounds *audio_objects);

bool					change_ambient_sources_state(t_ambient_sounds *ambient,
	t_source_state state);
bool					change_gui_sources_state(t_gui_sounds *gui,
	t_source_state state);
bool					change_objects_sources_state(t_objects_sounds *objects,
	t_source_state state);
bool					change_all_sources_state(t_sound_manager *manager,
	t_source_state state);

bool					update_ambient_amplitude(t_sound_manager *manager,
	t_ambient_sounds *ambient, float new_amplitude);
bool					update_gui_amplitude(t_sound_manager *manager,
	t_gui_sounds *gui, float new_amplitude);
bool					update_objects_amplitude(t_sound_manager *manager,
	t_objects_sounds *objects, float new_amplitude);
bool					update_global_amplitude(t_sound_manager *manager,
	float new_amplitude);

bool					slider_update_global_amplitude(void *value,
	void *manager);
bool					slider_update_ambient_amplitude(void *value,
	void *manager);
bool					slider_update_gui_amplitude(void *value,
	void *manager);
bool					slider_update_objects_amplitude(void *value,
	void *manager);
bool					slider_update_ambient_music_amplitude(void *value,
	void *manager);
bool					slider_update_game_over_music_amplitude(void *value,
	void *manager);
bool					slider_update_open_pause_amplitude(void *value,
	void *manager);
bool					slider_update_close_pause_amplitude(void *value,
	void *manager);
bool					slider_update_select_button_amplitude(void *value,
	void *manager);
bool					slider_update_start_of_level_amplitude(void *value,
	void *manager);
bool					slider_update_end_of_level_amplitude(void *value,
	void *manager);

/*
**	user_inputs
*/

void					set_default_user_inputs(t_user_inputs *user_inputs);
bool					is_scancode_user_input(t_user_inputs *user_inputs,
	SDL_Scancode scancode);

/*
**	input_button
*/

bool					draw_input_button_func(void *param);
bool					update_input_button_func(void *param);
t_gui_input_button		*create_input_button(const SDL_Rect rect,
	const t_color color, TTF_Font *font, t_env *env);
void					input_button_add_image(t_gui_input_button
	*input_button, SDL_Surface *surface);
void					input_button_remove_image(
	t_gui_input_button *input_button);
bool					destroy_input_button(
	t_gui_input_button **input_button);
bool					input_button_change_name(
	t_gui_input_button *input_button, const char *name);

/*
**	shortcuts
*/

void					init_shortcuts(t_shortcuts_inputs *shortcuts);
bool					is_input_game_over_shortcut(
	t_game_over_shortcuts *game_over, SDL_Scancode input);
bool					is_input_game_shortcut(t_game_shortcuts *game,
	SDL_Scancode input);
bool					is_input_editor_shortcut(t_editor_shortcuts *editor,
	SDL_Scancode input);
bool					is_input_menu_shortcut(t_menu_shortcuts *menu,
	SDL_Scancode input);

/*
**	pickup_object
*/

size_t					pickup_already_exists(t_env *env, t_vec3f *position);
int						add_pickup_object(t_env *env, t_vec3f *position,
	bool record);
int						add_pickup_object_p2(t_env *env, t_vec3f *position,
	t_sector *sector, bool record);
int						delete_pickup_object(t_env *env, t_vec3f *pos,
	bool record);
bool					draw_pickup_object(t_env *env, float dt);
void					draw_pickup_object_editor(t_env *env);
void					update_pickup_object(t_env *env);
bool					verify_objects_in_sector(t_env *env, t_sector *sector,
	bool check_inside);
bool					object_out_of_sector(t_env *env, t_point *point);

bool					init_remaining_object(t_env *env);
bool					init_object_manager(t_env *env);
void					destroy_object_manager(t_env *env);
void					free_remaining_objects(t_env *env);

bool					init_editor_game_state(t_env *env);
bool					destroy_select_texture_menu(
	t_selec_texure_menu *texture_menu);

bool					destroy_texture_menu(t_material_menu **texture_menu);
bool					destroy_sector_menu(t_sector_menu *sector_menu);

void					free_global_mesh(t_env *env);

bool					create_gui_main_menu(t_main_menu *main_menu,
							t_env *env);
bool					destroy_gui_main_menu(t_main_menu *main_menu);

t_scene					*create_main_menu_scene(t_env *env);
t_scene					*create_editor_scene(t_env *env);

bool					load_env_and_map(t_env **env, char **av);
bool					init_menu(t_env *env);
bool					destroy_menu(t_env *env);

bool					init_fonts(t_env *env);
void					free_fonts(t_env *env);

int						input(void *data, SDL_Event *event);

bool					draw_3d_sector_floor(t_sector *sector, t_env *env);
char					*get_file_name(char *path);

bool					check_valid_map(t_env *env);
bool					draw_level(t_env *env);

bool					init_game_audio(t_env *env);
void					free_all_event(t_env *env);
void					free_all_scene(t_env *env);
void					teleport_to_spawn(t_env *env);
void					free_pickup_object(t_doom_map *map);

/*
** game over
*/

void					game_over_animation(t_env *env);
bool					start_game_over_animation(t_env *env);
bool					init_game_over(t_env *env);
bool					init_game_over_menu(t_env *env);

bool					destroy_game_over_menu(t_game_over_menu *menu);
bool					create_game_over_menu(t_env *env,
	t_game_over_menu *menu);
void					init_game_over_gui_menu(t_env *env);
bool					init_texture_selection(t_material_menu *menu,
	t_material *material);
bool					destroy_win_menu(t_win_menu *menu);
bool					init_win_gui_menu(t_env *env);
bool					create_win_menu(t_env *env, t_win_menu *menu);
bool					init_win_state(t_env *env);
bool					init_win_menu(t_env *env);
void					init_editor_shortcut_p2(t_editor_shortcuts *editor);
void					free_all(t_env *env);
void					init_aabb(t_aabb *aabb);
void					update_aabb(t_aabb *aabb, t_vec3f *vec);
bool					inside_aabb(t_aabb *aabb, t_vec2f *vec);

void					check_new_map_option(char *option, t_env *env);
void					check_version_option(char **av, int ac);
bool					load_all_scene(t_env *env);

#endif
