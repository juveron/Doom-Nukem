/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:40:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/07 13:40:36 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void	active_worker(void)
{
	t_context_3d	*context_3d;

	context_3d = get_context()->context_3d;
	pthread_mutex_lock(&context_3d->mtx_work);
	context_3d->current_tile = 0;
	context_3d->finish = 0;
	pthread_mutex_lock(&context_3d->mtx_wait);
	context_3d->is_waiting = true;
	pthread_mutex_unlock(&context_3d->mtx_wait);
	context_3d->is_active = true;
	pthread_cond_broadcast(&context_3d->cond_work);
	pthread_mutex_unlock(&context_3d->mtx_work);
}

void	worker_wait(void)
{
	t_context_3d	*context_3d;

	context_3d = get_context()->context_3d;
	pthread_mutex_lock(&context_3d->mtx_wait);
	while (context_3d->is_waiting == true)
		pthread_cond_wait(&context_3d->cond_wait, &context_3d->mtx_wait);
	pthread_mutex_unlock(&context_3d->mtx_wait);
}
