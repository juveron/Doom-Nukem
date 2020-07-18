/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:22:31 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/03 17:25:02 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool	init_3d_context(void)
{
	t_context_3d	*context_3d;

	if (!(context_3d = ft_memalloc(sizeof(t_context_3d))))
		return (false);
	context_3d->is_alive = true;
	context_3d->finish = WORKER_THREAD;
	context_3d->use_depthbuffer = true;
	get_context()->context_3d = context_3d;
	return (true);
}

void	free_3d_context(void)
{
	t_context_3d	*context_3d;

	context_3d = get_context()->context_3d;
	free(context_3d);
}
