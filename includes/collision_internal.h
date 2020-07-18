/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 16:57:54 by thboura           #+#    #+#             */
/*   Updated: 2020/07/16 14:32:50 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_INTERNAL_H
# define COLLISION_INTERNAL_H

# include "internal_handler.h"

void	check_collision_p5(t_env *env, t_collision_handler *handler);
bool	check_collision_p8(t_env *env, t_collision_handler *handler);
void	collide(t_env *env, t_collision_handler *handler);
int		check_collision_p9(t_collision_handler *handler, t_env *env);
bool	check_collision_p2(t_env *env, t_collision_handler *handler,
	size_t i);
#endif
