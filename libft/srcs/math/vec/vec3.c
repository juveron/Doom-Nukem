/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:10:53 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/24 16:22:09 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3f		vec3f(float x, float y, float z)
{
	return ((t_vec3f){x, y, z});
}

t_vec3i		vec3i(int x, int y, int z)
{
	return ((t_vec3i){x, y, z});
}

t_vec3d		vec3d(double x, double y, double z)
{
	return ((t_vec3d){x, y, z});
}
