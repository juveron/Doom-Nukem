/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 09:59:13 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/26 10:05:43 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void	enable_depthbuffer(bool enable)
{
	get_context()->context_3d->use_depthbuffer = enable;
}
