/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:01:17 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/25 05:58:57 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3i		vec3i_mul(t_vec3i vec1, int mul)
{
	return ((t_vec3i){vec1.x * mul, vec1.y * mul, vec1.z * mul});
}

t_vec3f		vec3f_mul(t_vec3f vec1, float mul)
{
	return ((t_vec3f){vec1.x * mul, vec1.y * mul, vec1.z * mul});
}

t_vec3d		vec3d_mul(t_vec3d vec1, double mul)
{
	return ((t_vec3d){vec1.x * mul, vec1.y * mul, vec1.z * mul});
}
