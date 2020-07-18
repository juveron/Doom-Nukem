/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gravity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 10:55:14 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/12 17:14:13 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "physics.h"

void	update_gravity(const t_vec3f *gravity, t_physics_component *ph,
	const float dt, const double max_velocity)
{
	if (vec3f_length(ph->velocity) == max_velocity)
		return ;
	ph->velocity = vec3f_add(ph->velocity, vec3f_mul(*gravity, dt));
	if (vec3f_length(ph->velocity) > max_velocity)
		ph->velocity = vec3f_set_length(ph->velocity, max_velocity);
}

void	update_pos(t_vec3f *pos, t_physics_component *ph, const float dt)
{
	*pos = vec3f_add(*pos, vec3f_mul(ph->velocity, dt));
}
