/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 10:52:00 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/12 17:44:00 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include "libft.h"
# include "mysdl2.h"

# define DELTATIME 0.01

typedef struct	s_physics_component
{
	t_vec3f	velocity;
	t_vec3f	acceleration;
}				t_physics_component;

typedef struct	s_ph_context
{
	t_clock	physics_clock;
	double	new_time;
	double	frame_time;
	double	current_time;
	double	accumulator;
	double	dt;
	double	t;
	bool	(*update)(void *, float);
	void	*param;
}				t_ph_context;

void			ph_add_update_func(t_ph_context *ph_context,
	bool (*update)(void *, float), void *param);
void			update_gravity(const t_vec3f *gravity, t_physics_component *ph,
	const float dt, const double max_velocity);
void			update_pos(t_vec3f *pos, t_physics_component *ph,
	const float dt);
bool			ph_loop(t_ph_context *ph_context);
void			init_ph_context(t_ph_context *ph_context);
#endif
