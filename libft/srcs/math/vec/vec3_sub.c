/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:55:26 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/25 06:04:36 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_vec3i		vec3i_sub(t_vec3i vec1, t_vec3i vec2)
{
	return ((t_vec3i){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vec3f		vec3f_sub(t_vec3f vec1, t_vec3f vec2)
{
	return ((t_vec3f){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vec3d		vec3d_sub(t_vec3d vec1, t_vec3d vec2)
{
	return ((t_vec3d){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}
