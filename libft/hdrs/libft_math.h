/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 08:58:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 21:25:04 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MATH_H
# define LIBFT_MATH_H

# include <unistd.h>
# include "libft_bitsize.h"
# include <stdbool.h>
# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/*
**	Vectors
*/

typedef struct	s_vec2i
{
	int		x;
	int		y;
}				t_vec2i;

typedef struct	s_vec2ui
{
	unsigned int	x;
	unsigned int	y;
}				t_vec2ui;

typedef struct	s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

typedef struct	s_vec2d
{
	double	x;
	double	y;
}				t_vec2d;

typedef struct	s_vec2ld
{
	long double	x;
	long double	y;
}				t_vec2ld;

typedef struct	s_vec3i
{
	int		x;
	int		y;
	int		z;
}				t_vec3i;

typedef struct	s_vec3f
{
	float	x;
	float	y;
	float	z;
}				t_vec3f;

typedef struct	s_vec3d
{
	double	x;
	double	y;
	double	z;
}				t_vec3d;

typedef struct	s_vec4f
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vec4f;

/*
**	Complex
*/

typedef struct	s_complex
{
	double	r;
	double	i;
}				t_complex;

long			ft_pow(long nb, size_t e);
long			ft_log2(long n);
long			ft_log10(long n);

/*
**	max.c
*/

long			maxl(long a, long b);
int				maxi(int a, int b);
float			maxf(float a, float b);

/*
**	min.c
*/

long			minl(long a, long b);
int				mini(int a, int b);
float			minf(float a, float b);

/*
**	clamp.c
*/

long			clampl(long a, long min, long max);
int				clampi(int a, int min, int max);
float			clampf(float a, float min, float max);

/*
**	vec2f.c
*/

t_vec2f			vec2f_from_angle(float angle);

/*
**	vec2.c
*/

t_vec2f			vec2f(float x, float y);
t_vec2i			vec2i(int x, int y);
t_vec2d			vec2d(double x, double y);
t_vec2ui		vec2ui(t_u32 x, t_u32 y);

/*
**	vec2_add.c
*/

t_vec2i			vec2i_add(t_vec2i vec1, t_vec2i vec2);
t_vec2f			vec2f_add(t_vec2f vec1, t_vec2f vec2);
t_vec2d			vec2d_add(t_vec2d vec1, t_vec2d vec2);
t_vec2ui		vec2ui_add(t_vec2ui vec1, t_vec2ui vec2);

/*
**	vec2_cross.c
*/

float			vec2f_cross(t_vec2f vec1, t_vec2f vec2);
float			vec2i_cross(t_vec2i vec1, t_vec2i vec2);
float			vec2d_cross(t_vec2d vec1, t_vec2d vec2);
float			vec2ui_cross(t_vec2ui vec1, t_vec2ui vec2);

/*
**	vec2_dist_sq.c
*/

float			vec2i_dist_sq(t_vec2i vec1, t_vec2i vec2);
float			vec2f_dist_sq(t_vec2f vec1, t_vec2f vec2);
float			vec2d_dist_sq(t_vec2d vec1, t_vec2d vec2);
float			vec2ui_dist_sq(t_vec2ui vec1, t_vec2ui vec2);

/*
**	vec2_dist.c
*/

float			vec2i_dist(t_vec2i vec1, t_vec2i vec2);
float			vec2f_dist(t_vec2f vec1, t_vec2f vec2);
float			vec2d_dist(t_vec2d vec1, t_vec2d vec2);
float			vec2ui_dist(t_vec2ui vec1, t_vec2ui vec2);

/*
**	vec2_div.c
*/

t_vec2i			vec2i_div(t_vec2i vec1, int div);
t_vec2ui		vec2ui_div(t_vec2ui vec1, t_u32 div);
t_vec2f			vec2f_div(t_vec2f vec1, float div);
t_vec2d			vec2d_div(t_vec2d vec1, double div);

/*
**	vec2_dot.c
*/

float			vec2i_dot(t_vec2i vec1, t_vec2i vec2);
float			vec2f_dot(t_vec2f vec1, t_vec2f vec2);
float			vec2d_dot(t_vec2d vec1, t_vec2d vec2);
float			vec2ui_dot(t_vec2ui vec1, t_vec2ui vec2);

/*
**	vec2_length_sq.c
*/

float			vec2i_length_sq(t_vec2i vec1);
float			vec2f_length_sq(t_vec2f vec1);
float			vec2d_length_sq(t_vec2d vec1);
float			vec2ui_length_sq(t_vec2ui vec1);

/*
**	vec2_length.c
*/

float			vec2i_length(t_vec2i vec1);
float			vec2f_length(t_vec2f vec1);
float			vec2d_length(t_vec2d vec1);
float			vec2ui_length(t_vec2ui vec1);

/*
**	vec2_mul.c
*/

t_vec2i			vec2i_mul(t_vec2i vec1, int mul);
t_vec2ui		vec2ui_mul(t_vec2ui vec1, t_u32 mul);
t_vec2f			vec2f_mul(t_vec2f vec1, float mul);
t_vec2d			vec2d_mul(t_vec2d vec1, double mul);

/*
**	vec2_normal.c
*/

t_vec2i			vec2i_normal(t_vec2i vec1);
t_vec2f			vec2f_normal(t_vec2f vec1);
t_vec2d			vec2d_normal(t_vec2d vec1);
t_vec2ui		vec2ui_normal(t_vec2ui vec1);

/*
**	vec2_normalize.c
*/

t_vec2f			vec2i_normalize(t_vec2i vec1);
t_vec2f			vec2f_normalize(t_vec2f vec1);
t_vec2d			vec2d_normalize(t_vec2d vec1);
t_vec2f			vec2ui_normalize(t_vec2ui vec1);

/*
**	vec2_project.c
*/

t_vec2i			vec2i_project(t_vec2i vec1, t_vec2i vec2);
t_vec2f			vec2f_project(t_vec2f vec1, t_vec2f vec2);
t_vec2d			vec2d_project(t_vec2d vec1, t_vec2d vec2);
t_vec2ui		vec2ui_project(t_vec2ui vec1, t_vec2ui vec2);

/*
**	vec2_set_length.c
*/

t_vec2i			vec2i_set_length(t_vec2i vec1, int len);
t_vec2f			vec2f_set_length(t_vec2f vec1, float len);
t_vec2d			vec2d_set_length(t_vec2d vec1, double len);
t_vec2ui		vec2ui_set_length(t_vec2ui vec1, t_u32 len);

/*
**	vec2_sub.c
*/

t_vec2i			vec2i_sub(t_vec2i vec1, t_vec2i vec2);
t_vec2f			vec2f_sub(t_vec2f vec1, t_vec2f vec2);
t_vec2d			vec2d_sub(t_vec2d vec1, t_vec2d vec2);
t_vec2ui		vec2ui_sub(t_vec2ui vec1, t_vec2ui vec2);

/*
**	vec3.c
*/

t_vec3f			vec3f(float x, float y, float z);
t_vec3i			vec3i(int x, int y, int z);
t_vec3d			vec3d(double x, double y, double z);

/*
**	vec3_add.c
*/

t_vec3i			vec3i_add(t_vec3i vec1, t_vec3i vec2);
t_vec3f			vec3f_add(t_vec3f vec1, t_vec3f vec2);
t_vec3d			vec3d_add(t_vec3d vec1, t_vec3d vec2);

/*
**	vec3_cross.c
*/

t_vec3f			vec3f_cross(t_vec3f vec1, t_vec3f vec2);
t_vec3i			vec3i_cross(t_vec3i vec1, t_vec3i vec2);
t_vec3d			vec3d_cross(t_vec3d vec1, t_vec3d vec2);

/*
**	vec3_dist_sq
*/

float			vec3i_dist_sq(t_vec3i vec1, t_vec3i vec2);
float			vec3f_dist_sq(t_vec3f vec1, t_vec3f vec2);
float			vec3d_dist_sq(t_vec3d vec1, t_vec3d vec2);

/*
**	vec3_dist.c
*/

float			vec3i_dist(t_vec3i vec1, t_vec3i vec2);
float			vec3f_dist(t_vec3f vec1, t_vec3f vec2);
float			vec3d_dist(t_vec3d vec1, t_vec3d vec2);

/*
**	vec3_div.c
*/

t_vec3i			vec3i_div(t_vec3i vec1, int div);
t_vec3f			vec3f_div(t_vec3f vec1, float div);
t_vec3d			vec3d_div(t_vec3d vec1, double div);

/*
**	vec3_dot.c
*/

float			vec3i_dot(t_vec3i vec1, t_vec3i vec2);
float			vec3f_dot(t_vec3f vec1, t_vec3f vec2);
float			vec3d_dot(t_vec3d vec1, t_vec3d vec2);

/*
**	vec3_length_sq.c
*/

float			vec3i_length_sq(t_vec3i vec1);
float			vec3f_length_sq(t_vec3f vec1);
float			vec3d_length_sq(t_vec3d vec1);

/*
**	vec3_length.c
*/

float			vec3i_length(t_vec3i vec1);
float			vec3f_length(t_vec3f vec1);
float			vec3d_length(t_vec3d vec1);

/*
**	vec3_mul.c
*/

t_vec3i			vec3i_mul(t_vec3i vec1, int mul);
t_vec3f			vec3f_mul(t_vec3f vec1, float mul);
t_vec3d			vec3d_mul(t_vec3d vec1, double mul);

/*
**	vec3_normalize.c
*/

t_vec3f			vec3i_normalize(t_vec3i vec1);
t_vec3f			vec3f_normalize(t_vec3f vec1);
t_vec3d			vec3d_normalize(t_vec3d vec1);

/*
**	vec3_set_length.c
*/

t_vec3i			vec3i_set_length(t_vec3i vec1, int len);
t_vec3f			vec3f_set_length(t_vec3f vec1, float len);
t_vec3d			vec3d_set_length(t_vec3d vec1, double len);

/*
**	vec3_sub.c
*/

t_vec3i			vec3i_sub(t_vec3i vec1, t_vec3i vec2);
t_vec3f			vec3f_sub(t_vec3f vec1, t_vec3f vec2);
t_vec3d			vec3d_sub(t_vec3d vec1, t_vec3d vec2);

/*
**	vec3.c
*/

t_vec3f			vec3f(float x, float y, float z);
t_vec3i			vec3i(int x, int y, int z);
t_vec3d			vec3d(double x, double y, double z);

t_vec2f			vec2f_from_angle(float angle);
float			radian(float degre);

t_vec4f			vec4f_div(t_vec4f vec, float d);
t_vec4f			vec4f_sub(t_vec4f vec1, t_vec4f vec2);
t_vec4f			vec4f_cross(t_vec4f vec1, t_vec4f vec2);
t_vec4f			vec4f_normalize(t_vec4f vec1);
float			vec4f_dot(t_vec4f vec1, t_vec4f vec2);
t_vec4f			vec4f_add(t_vec4f vec1, t_vec4f vec2);
t_vec4f			vec4f_mul(t_vec4f vec, float d);
t_vec4f			vec4f(float x, float y, float z, float w);
float			vec4f_dist(t_vec4f vec1, t_vec4f vec2);

float			lerpf(float v0, float v1, float t);
int				lerpi(int min, int max, float t);
bool			vec3f_equal(t_vec3f *vec1, t_vec3f *vec2);

#endif
