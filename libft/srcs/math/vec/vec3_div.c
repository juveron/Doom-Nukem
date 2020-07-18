/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:17:51 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/25 05:55:04 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3i		vec3i_div(t_vec3i vec1, int div)
{
	return ((t_vec3i){vec1.x / div, vec1.y / div, vec1.z / div});
}

t_vec3f		vec3f_div(t_vec3f vec1, float div)
{
	return ((t_vec3f){vec1.x / div, vec1.y / div, vec1.z / div});
}

t_vec3d		vec3d_div(t_vec3d vec1, double div)
{
	return ((t_vec3d){vec1.x / div, vec1.y / div, vec1.z / div});
}
