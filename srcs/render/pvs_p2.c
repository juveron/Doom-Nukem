/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pvs_p2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:57:32 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 15:57:33 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "pvs_internal.h"

void		portal_partially_in_vf(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2)
{
	pvs2->s.available = true;
	portal_partially_in_vf_end(pvs, pvs2);
	if (vec3f_cross(vec3f_sub(pvs->s.start1, pvs2->s.end1),
					vec3f_sub(pvs->wall->v1->v.v, pvs2->s.end1)).y > 0)
		pvs2->s.start1 = pvs->s.start1;
	else
		pvs2->s.start1 = pvs->wall->v1->v.v;
	if (vec3f_cross(vec3f_sub(pvs->s.start2, pvs2->s.end2),
					vec3f_sub(pvs->wall->v2->v.v, pvs2->s.end2)).y < 0)
		pvs2->s.start2 = pvs->s.start2;
	else
		pvs2->s.start2 = pvs->wall->v2->v.v;
	pvs2->s.sector = pvs->s.sector;
	pvs2->s.iter = pvs->s.iter + 1;
}

static void	compute_line(t_pvs_handle_2 *pvs)
{
	t_vec3f	v1;
	t_vec3f v2;

	v1 = vec3f_sub(pvs->s.end1, pvs->s.start1);
	v2 = vec3f_sub(pvs->s.end2, pvs->s.start2);
	pvs->check[0] = vec3f_cross_v2(v1, vec3f_sub(pvs->wall_i->v2->v.v,
			pvs->s.start1));
	pvs->check[1] = vec3f_cross_v2(v1, vec3f_sub(pvs->wall_i->v1->v.v,
			pvs->s.start1));
	pvs->check[2] = vec3f_cross_v2(v2, vec3f_sub(pvs->wall_i->v2->v.v,
			pvs->s.start2));
	pvs->check[3] = vec3f_cross_v2(v2, vec3f_sub(pvs->wall_i->v1->v.v,
			pvs->s.start2));
}

static int	compute_portal_p2(t_pvs_handle_2 *pvs)
{
	t_pvs_handle_2	pvs2;

	if ((pvs->check[0] <= 0.f && pvs->check[1] <= 0.f)
		|| (pvs->check[2] >= 0.f && pvs->check[3] >= 0.f))
		return (0);
	copy_pvs(pvs, &pvs2);
	portal_partially_in_vf(pvs, &pvs2);
	if (!compute_pvs_internal(&pvs2))
		return (-1);
	return (1);
}

static int	compute_portal(t_pvs_handle_2 *pvs)
{
	t_pvs_handle_2	pvs2;

	if (pvs->s.available)
		compute_line(pvs);
	if (!pvs->s.available)
	{
		copy_pvs(pvs, &pvs2);
		compute_first_portal(pvs, &pvs2);
		if (!compute_pvs_internal(&pvs2))
			return (-1);
		return (1);
	}
	else if (pvs->check[0] > 0.f && pvs->check[1] > 0.f
		&& pvs->check[2] < 0.f && pvs->check[3] < 0.f)
	{
		copy_pvs(pvs, &pvs2);
		portal_in_vf(pvs, &pvs2);
		if (!compute_pvs_internal(&pvs2))
			return (-1);
		return (1);
	}
	else
		return (compute_portal_p2(pvs));
}

int			compute_pvs_internal_p2(t_pvs_handle_2 *pvs)
{
	if ((vec3f_cross_v2(vec3f_sub(pvs->wall->v2->v.v, pvs->wall->v1->v.v),
			vec3f_sub(pvs->wall_i->v2->v.v, pvs->wall->v1->v.v)) <= 0
		&& vec3f_cross_v2(vec3f_sub(pvs->wall->v1->v.v, pvs->wall->v2->v.v),
			vec3f_sub(pvs->wall_i->v1->v.v, pvs->wall->v2->v.v)) >= 0)
		|| (vec3f_cross_v2(vec3f_sub(pvs->wall_i->v2->v.v,
			pvs->wall_i->v1->v.v), vec3f_sub(pvs->wall->v2->v.v,
			pvs->wall_i->v1->v.v)) >= 0
		&& vec3f_cross_v2(vec3f_sub(pvs->wall_i->v1->v.v, pvs->wall_i->v2->v.v),
			vec3f_sub(pvs->wall->v1->v.v, pvs->wall_i->v2->v.v)) <= 0))
		return (0);
	return (compute_portal(pvs));
}
