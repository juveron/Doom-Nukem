/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:21:47 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/24 16:33:13 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_vec3f	vec3f_cross(t_vec3f vec1, t_vec3f vec2)
{
	return ((t_vec3f){vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x});
}

t_vec3i	vec3i_cross(t_vec3i vec1, t_vec3i vec2)
{
	return ((t_vec3i){vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x});
}

t_vec3d	vec3d_cross(t_vec3d vec1, t_vec3d vec2)
{
	return ((t_vec3d){vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x});
}
