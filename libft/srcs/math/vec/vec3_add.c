/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:51:17 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/24 16:24:55 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_vec3i		vec3i_add(t_vec3i vec1, t_vec3i vec2)
{
	return ((t_vec3i){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec3f		vec3f_add(t_vec3f vec1, t_vec3f vec2)
{
	return ((t_vec3f){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec3d		vec3d_add(t_vec3d vec1, t_vec3d vec2)
{
	return ((t_vec3d){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}
