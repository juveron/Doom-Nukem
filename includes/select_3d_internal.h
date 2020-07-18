/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_3d_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:11:59 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/17 18:04:46 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_3D_INTERNAL_H
# define SELECT_3D_INTERNAL_H

# include "editor.h"

typedef struct	s_selec_internal
{
	t_sector	*sector;
	t_wall		*wall;
	float		dist;
	t_ray		ray;
	t_env		*env;
	int			ret;
}				t_selec_internal;

bool			ray_intersect_triangle(t_selec_internal *selec,
	t_triangle *triangle, t_vec3f *out);
t_vec3f			get_normal(t_triangle *tri);
void			check_selection_ceil(t_selec_internal *s);
void			check_selection_floor(t_selec_internal *s);
bool			check_triangle_vector(t_selec_internal *s, t_vector *triangle);
void			check_wall(t_selec_internal *s);
bool			init_right_menu(t_env *env);

#endif
