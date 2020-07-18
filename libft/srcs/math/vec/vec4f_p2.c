/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4f_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 21:28:25 by thboura           #+#    #+#             */
/*   Updated: 2020/05/30 21:28:39 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_vec4f	vec4f_cross(t_vec4f vec1, t_vec4f vec2)
{
	return ((t_vec4f){vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x,
		vec1.w});
}

float	vec4f_dot(t_vec4f vec1, t_vec4f vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float	vec4f_length(t_vec4f vec1)
{
	return (sqrtf(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z));
}

t_vec4f	vec4f_normalize(t_vec4f vec1)
{
	float	len;

	len = vec4f_length(vec1);
	return ((t_vec4f){vec1.x / len, vec1.y / len, vec1.z / len, vec1.w});
}

float	vec4f_dist(t_vec4f vec1, t_vec4f vec2)
{
	return (vec4f_length((t_vec4f){vec2.x - vec1.x, vec2.y - vec1.y,
		vec2.z - vec1.z, 1}));
}
