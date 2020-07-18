/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:14:59 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/14 10:16:43 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLIDER_H
# define COLLIDER_H

# include "mysdl2.h"

typedef struct	s_capsule_collider
{
	t_vec3f	start;
	t_vec3f	end;
	float	radius;
}				t_capsule_collider;

typedef struct	s_segment
{
	t_vec3f	a;
	t_vec3f	b;
}				t_segment;

typedef struct	s_segment_dist
{
	t_vec3f	u;
	t_vec3f	v;
	t_vec3f	w;
	float	a;
	float	b;
	float	c;
	float	d;
	float	e;
	float	caps_d;
	float	sc;
	float	sn;
	float	sd;
	float	tc;
	float	tn;
	float	td;
}				t_segment_dist;

typedef struct	s_capsule_handler
{
	t_vec3f	normal;
	float	dist;
}				t_capsule_handler;

t_vec3f			segment_dist(const t_vec3f *s11, const t_vec3f *s12,
	const t_vec3f *s21, const t_vec3f *s22);
bool			capsule_triangle_check(t_vec3f *closest,
	t_capsule_collider *capsule, t_triangle *triangle);
bool			project_point_triangle(t_vec3f *proj, const t_vec3f *point,
	const t_triangle *triangle, const t_vec3f *normal);

#endif
