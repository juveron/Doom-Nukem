/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule_collider.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:04:07 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/06 12:10:27 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collider.h"

static void	init(t_segment_dist *dist)
{
	dist->a = vec3f_dot(dist->u, dist->u);
	dist->b = vec3f_dot(dist->u, dist->v);
	dist->c = vec3f_dot(dist->v, dist->v);
	dist->d = vec3f_dot(dist->u, dist->w);
	dist->e = vec3f_dot(dist->v, dist->w);
	dist->caps_d = dist->a * dist->c - dist->b * dist->b;
	dist->sc = dist->caps_d;
	dist->sn = dist->caps_d;
	dist->sd = dist->caps_d;
	dist->tc = dist->caps_d;
	dist->tn = dist->caps_d;
	dist->td = dist->caps_d;
}

static void	segment_dist_p2(t_segment_dist *dist)
{
	if (dist->caps_d < 0.0000001f)
	{
		dist->sn = 0.f;
		dist->sd = 1.f;
		dist->tn = dist->e;
		dist->td = dist->c;
	}
	else
	{
		dist->sn = dist->b * dist->e - dist->c * dist->d;
		dist->tn = dist->a * dist->e - dist->b * dist->d;
		if (dist->sn < 0.f)
		{
			dist->sn = 0.f;
			dist->tn = dist->e;
			dist->td = dist->c;
		}
		else if (dist->sn > dist->sd)
		{
			dist->sn = dist->sd;
			dist->tn = dist->e + dist->b;
			dist->td = dist->c;
		}
	}
}

static void	segment_dist_p3(t_segment_dist *dist)
{
	dist->tn = 0.f;
	if (-dist->d < 0.f)
		dist->sn = 0.f;
	else if (-dist->d > dist->a)
		dist->sn = dist->sd;
	else
	{
		dist->sn = -dist->d;
		dist->sd = dist->a;
	}
}

static void	segment_dist_p4(t_segment_dist *dist)
{
	dist->tn = dist->td;
	if (-dist->d + dist->b < 0.f)
		dist->sn = 0.f;
	else if (-dist->d + dist->b > dist->a)
		dist->sn = dist->sd;
	else
	{
		dist->sn = -dist->d + dist->b;
		dist->sd = dist->a;
	}
}

t_vec3f		segment_dist(const t_vec3f *s11, const t_vec3f *s12,
	const t_vec3f *s21, const t_vec3f *s22)
{
	t_segment_dist	dist;
	t_vec3f			a;
	t_vec3f			b;
	t_vec3f			dp;

	dist.u = vec3f_sub(*s12, *s11);
	dist.v = vec3f_sub(*s22, *s21);
	dist.w = vec3f_sub(*s11, *s21);
	init(&dist);
	segment_dist_p2(&dist);
	if (dist.tn < 0.f)
		segment_dist_p3(&dist);
	else if (dist.tn > dist.td)
		segment_dist_p4(&dist);
	dist.sc = fabsf(dist.sn) < 0.0000001f ? 0.f : dist.sn / dist.sd;
	dist.tc = fabsf(dist.tn) < 0.0000001f ? 0.f : dist.tn / dist.td;
	a = vec3f_mul(dist.u, dist.sc);
	b = vec3f_mul(dist.v, dist.tc);
	dp = vec3f_add(dist.w, vec3f_sub(a, b));
	return (dp);
}
