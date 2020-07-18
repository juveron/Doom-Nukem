/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pvs_p3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:57:42 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 15:57:43 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "pvs_internal.h"

void	portal_compute_start(t_pvs_handle_2 *pvs,
											t_pvs_handle_2 *pvs2)
{
	if (vec3f_cross_v2(vec3f_sub(pvs->wall_i->v2->v.v, pvs->wall_i->v1->v.v),
			vec3f_sub(pvs->s.start2, pvs->wall_i->v1->v.v)) > 0)
	{
		pvs2->s.start2 = vec2_to_vec3(line_line_intersect(
				vec3_to_vec2(&pvs->s.start2), vec3_to_vec2(&pvs->s.start1),
				vec3_to_vec2(&pvs->wall_i->v1->v.v),
				vec3_to_vec2(&pvs->wall_i->v2->v.v)));
	}
	else
		pvs2->s.start2 = pvs->s.start2;
	if (vec3f_cross_v2(vec3f_sub(pvs->wall_i->v1->v.v, pvs->wall_i->v2->v.v),
			vec3f_sub(pvs->s.start1, pvs->wall_i->v2->v.v)) < 0)
	{
		pvs2->s.start1 = vec2_to_vec3(line_line_intersect(
				vec3_to_vec2(&pvs->s.start2), vec3_to_vec2(&pvs->s.start1),
				vec3_to_vec2(&pvs->wall_i->v1->v.v),
				vec3_to_vec2(&pvs->wall_i->v2->v.v)));
	}
	else
		pvs2->s.start1 = pvs->s.start1;
}

void	portal_compute_end(t_pvs_handle_2 *pvs,
		t_pvs_handle_2 *pvs2)
{
	if (vec3f_cross_v2(vec3f_sub(pvs2->s.start2, pvs2->s.start1),
			vec3f_sub(pvs->wall_i->v2->v.v, pvs2->s.start1)) < 0)
	{
		pvs2->s.end1 = vec2_to_vec3(line_line_intersect(
				vec3_to_vec2(&pvs2->s.start2), vec3_to_vec2(&pvs2->s.start1),
				vec3_to_vec2(&pvs->wall_i->v1->v.v),
				vec3_to_vec2(&pvs->wall_i->v2->v.v)));
	}
	else
		pvs2->s.end1 = pvs->wall_i->v2->v.v;
	if (vec3f_cross_v2(vec3f_sub(pvs2->s.start2, pvs2->s.start1),
			vec3f_sub(pvs->wall_i->v1->v.v, pvs2->s.start1)) < 0)
	{
		pvs2->s.end2 = vec2_to_vec3(line_line_intersect(
				vec3_to_vec2(&pvs2->s.start2), vec3_to_vec2(&pvs2->s.start1),
				vec3_to_vec2(&pvs->wall_i->v1->v.v),
				vec3_to_vec2(&pvs->wall_i->v2->v.v)));
	}
	else
		pvs2->s.end2 = pvs->wall_i->v1->v.v;
}

void	portal_partially_in_vf_end(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2)
{
	if (pvs->check[0] < 0.f != pvs->check[1] < 0.f)
	{
		pvs2->s.end1 = vec2_to_vec3(line_line_intersect(
				vec3_to_vec2(&pvs->s.end1), vec3_to_vec2(&pvs->s.start1),
				vec3_to_vec2(&pvs->wall_i->v1->v.v),
				vec3_to_vec2(&pvs->wall_i->v2->v.v)));
	}
	else
		pvs2->s.end1 = pvs->wall_i->v2->v.v;
	if (pvs->check[2] > 0.f != pvs->check[3] > 0.f)
	{
		pvs2->s.end2 = vec2_to_vec3(line_line_intersect(
				vec3_to_vec2(&pvs->s.end2), vec3_to_vec2(&pvs->s.start2),
				vec3_to_vec2(&pvs->wall_i->v1->v.v),
				vec3_to_vec2(&pvs->wall_i->v2->v.v)));
	}
	else
		pvs2->s.end2 = pvs->wall_i->v1->v.v;
}

void	compute_first_portal(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2)
{
	portal_compute_start(pvs, pvs2);
	portal_compute_end(pvs, pvs2);
	pvs2->s.available = true;
	pvs2->s.sector = pvs->s.sector;
	pvs2->s.iter = pvs->s.iter + 1;
}

void	portal_in_vf(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2)
{
	portal_compute_start(pvs, pvs2);
	pvs2->s.end1 = pvs->wall_i->v2->v.v;
	pvs2->s.end2 = pvs->wall_i->v1->v.v;
	pvs2->s.available = true;
	pvs2->s.sector = pvs->s.sector;
	pvs2->s.iter = pvs->s.iter + 1;
}
