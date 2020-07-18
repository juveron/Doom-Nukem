/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:59:31 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/25 05:53:15 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	vec3i_dist(t_vec3i vec1, t_vec3i vec2)
{
	return (vec3i_length((t_vec3i){vec2.x - vec1.x, vec2.y - vec1.y,
		vec2.z - vec1.z}));
}

float	vec3f_dist(t_vec3f vec1, t_vec3f vec2)
{
	return (vec3f_length((t_vec3f){vec2.x - vec1.x, vec2.y - vec1.y,
		vec2.z - vec1.z}));
}

float	vec3d_dist(t_vec3d vec1, t_vec3d vec2)
{
	return (vec3d_length((t_vec3d){vec2.x - vec1.x, vec2.y - vec1.y,
		vec2.z - vec1.z}));
}
