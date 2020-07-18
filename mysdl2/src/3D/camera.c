/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:51:26 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/30 11:33:42 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void	update_camera(t_camera *camera)
{
	update_transform(&camera->transform);
	camera->m_invert = matrix_invert2(camera->transform.rot_pos);
}
