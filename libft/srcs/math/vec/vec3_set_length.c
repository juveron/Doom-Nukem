/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_set_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:06:30 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 21:26:55 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3i		vec3i_set_length(t_vec3i vec1, int len)
{
	t_vec3f	norm;

	norm = vec3i_normalize(vec1);
	return ((t_vec3i){norm.x * (float)len, norm.y * (float)len,
		norm.z * (float)len});
}

t_vec3f		vec3f_set_length(t_vec3f vec1, float len)
{
	t_vec3f	norm;

	norm = vec3f_normalize(vec1);
	return ((t_vec3f){norm.x * (float)len, norm.y * (float)len,
		norm.z * (float)len});
}

t_vec3d		vec3d_set_length(t_vec3d vec1, double len)
{
	t_vec3d	norm;

	norm = vec3d_normalize(vec1);
	return ((t_vec3d){norm.x * (double)len, norm.y * (double)len,
		norm.z * (float)len});
}
