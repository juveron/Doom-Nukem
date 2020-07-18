/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:07:13 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:10:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

static void	check_wait_cond(t_context_3d *context_3d)
{
	if (context_3d->current_tile >= context_3d->tile_max)
	{
		pthread_mutex_lock(&context_3d->mtx_wait);
		context_3d->is_active = false;
		if (context_3d->finish == 0)
		{
			context_3d->is_waiting = false;
			pthread_cond_signal(&context_3d->cond_wait);
		}
		pthread_mutex_unlock(&context_3d->mtx_wait);
	}
}

bool		get_work(t_context_3d *context_3d, t_u16 *current_tile)
{
	pthread_mutex_lock(&context_3d->mtx_work);
	context_3d->finish--;
	check_wait_cond(context_3d);
	while (context_3d->is_active == false
		|| context_3d->current_tile >= context_3d->tile_max)
	{
		pthread_cond_wait(&context_3d->cond_work,
			&context_3d->mtx_work);
	}
	context_3d->finish++;
	if (context_3d->is_alive == false)
		return (false);
	*current_tile = context_3d->current_tile++;
	pthread_mutex_unlock(&context_3d->mtx_work);
	return (true);
}

void		*rasterizer_worker_function(void *arg)
{
	t_tile				*tile;
	t_context_3d		*context_3d;
	t_u16				current_tile;

	(void)arg;
	context_3d = get_context()->context_3d;
	while (1)
	{
		if (!get_work(context_3d, &current_tile))
			break ;
		tile = &context_3d->render_screen.tiles[current_tile];
		if (!draw_tile(tile))
		{
			get_context()->run = false;
			return (NULL);
		}
	}
	pthread_mutex_unlock(&context_3d->mtx_work);
	return (NULL);
}

void		destroy_rasterizer_workers(void)
{
	t_context_3d		*context_3d;
	size_t				i;
	t_rasterizer_worker	*worker;

	context_3d = get_context()->context_3d;
	i = 0;
	context_3d->is_alive = false;
	active_worker();
	while (i < WORKER_THREAD)
	{
		worker = &context_3d->workers[i];
		if (worker->thread)
		{
			if (pthread_join(worker->thread, NULL))
				ft_dprintf(2, "Fail to join thread !\n");
		}
		i++;
	}
}

bool		init_rasterizer_worker(void)
{
	t_context_3d		*context_3d;
	size_t				i;
	t_rasterizer_worker	*worker;

	context_3d = get_context()->context_3d;
	pthread_mutex_init(&context_3d->mtx_wait, NULL);
	pthread_mutex_init(&context_3d->mtx_work, NULL);
	pthread_cond_init(&context_3d->cond_wait, NULL);
	pthread_cond_init(&context_3d->cond_work, NULL);
	i = 0;
	while (i < WORKER_THREAD)
	{
		worker = &context_3d->workers[i];
		worker->id = i;
		if (pthread_create(&worker->thread, NULL,
			&rasterizer_worker_function, worker))
		{
			destroy_rasterizer_workers();
			return (false);
		}
		i++;
	}
	return (true);
}
