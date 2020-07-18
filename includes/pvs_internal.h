/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pvs_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 10:17:31 by thboura           #+#    #+#             */
/*   Updated: 2020/07/14 10:17:37 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PVS_INTERNAL_H
# define PVS_INTERNAL_H

# include "render.h"

void	copy_pvs(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2);
t_vec2f	vec3_to_vec2(t_vec3f *v);
t_vec3f	vec2_to_vec3(t_vec2f v);
t_vec2f	line_line_intersect(t_vec2f a, t_vec2f b, t_vec2f c, t_vec2f d);
float	vec3f_cross_v2(t_vec3f vec1, t_vec3f vec2);
void	portal_compute_start(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2);
void	portal_compute_end(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2);
void	portal_in_vf(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2);
void	compute_first_portal(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2);
void	portal_partially_in_vf_end(t_pvs_handle_2 *pvs, t_pvs_handle_2 *pvs2);
int		compute_pvs_internal_p2(t_pvs_handle_2 *pvs);

#endif
