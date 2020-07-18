/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 13:04:37 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 21:26:16 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3f		vec3i_normalize(t_vec3i vec1)
{
	float	len;

	len = vec3i_length(vec1);
	return ((t_vec3f){vec1.x / len, vec1.y / len, vec1.z / len});
}

t_vec3f		vec3f_normalize(t_vec3f vec1)
{
	float	len;

	len = vec3f_length(vec1);
	return ((t_vec3f){vec1.x / len, vec1.y / len, vec1.z / len});
}

t_vec3d		vec3d_normalize(t_vec3d vec1)
{
	float	len;

	len = vec3d_length(vec1);
	return ((t_vec3d){vec1.x / len, vec1.y / len, vec1.z / len});
}
