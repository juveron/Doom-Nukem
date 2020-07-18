/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:31:48 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 17:24:05 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "doom_nukem.h"

typedef struct	s_ray_intersect
{
	t_vec3f edge1;
	t_vec3f edge2;
	t_vec3f	h;
	float	a;
	float	f;
	t_vec3f	s;
	t_vec3f	q;
	float	u;
	float	v;
	float	t;
}				t_ray_intersect;

t_vec2i			grid_to_win(t_vec3f *vec, t_env *env);
void			draw_new_sector(t_env *env);

void			set_grid_info(t_env *env);
void			draw_grid(t_env *env);

void			draw_sectors(t_env *env);

void			get_snap_point(t_env *env);
void			draw_snap_point(t_env *env);

void			free_point(t_point *point);

bool			vaild_wall_position(t_vec3f *v1, t_vec3f *v2, t_env *env);
bool			close_sector(t_env *env, t_wall *tmp, t_wall *walls, size_t j);

bool			redo_point(t_env *env, void *param);
bool			move_texture_window(void *target, void *param);
bool			close_texture_window(void *target, void *param);
bool			show_texture_window(void *param);

void			destory_select_texture_menu(t_selec_texure_menu *texture_menu);
t_color			get_random_color(void);

void			get_closest_wall(t_env *env);
void			draw_sector_highlight(t_sector *sector, t_env *env,
	t_color color);

bool			show_pvs(t_sector *sector, t_env *env);
bool			selec(t_env *env);
bool			undo_sector(t_env *env, void *param);
t_sector		*sector_clone2(t_sector *sector, t_vector *vertices);
void			update_height(t_sector *sector, t_env *env);
void			clear_event(t_env *env);
bool			update_texture_info(void *param, void *data);
bool			insert_by_correct_wall(t_wall *verif_wall, t_wall *src_wall,
		t_sector *sector, size_t *i);

#endif
