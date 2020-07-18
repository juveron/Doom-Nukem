/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 03:42:26 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/15 02:15:08 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_game	*create_game_struct(void)
{
	t_game	*game;

	if (!(game = ft_memalloc(sizeof(t_game))))
		return (NULL);
	return (game);
}

void	destroy_game_struct(t_game **game)
{
	vector_free(&(*game)->visible_sector);
	free(*game);
	*game = NULL;
}

void	init_game_struct(t_game *game)
{
	game->current_segment_time = 0;
	game->highscore = 0;
}
