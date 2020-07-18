/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:36:33 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 21:28:03 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

t_vec4f	vec4f(float x, float y, float z, float w)
{
	return ((t_vec4f){x, y, z, w});
}

t_vec4f	vec4f_div(t_vec4f vec, float d)
{
	return ((t_vec4f){vec.x / d, vec.y / d, vec.z / d, vec.w});
}

t_vec4f	vec4f_mul(t_vec4f vec, float d)
{
	return ((t_vec4f){vec.x * d, vec.y * d, vec.z * d, vec.w});
}

t_vec4f	vec4f_add(t_vec4f vec1, t_vec4f vec2)
{
	return ((t_vec4f){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z,
		vec1.w});
}

t_vec4f	vec4f_sub(t_vec4f vec1, t_vec4f vec2)
{
	return ((t_vec4f){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z,
		vec1.w});
}
