/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 21:27:19 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/19 11:13:28 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	exit_doom(t_env *env)
{
	free_env(env);
	free_3d_context();
	free_context();
	exit(EXIT_SUCCESS);
}

void	throw_error(char *msg, t_env *env)
{
	ft_dprintf(2, "%s\n", msg);
	free_env(env);
	free_3d_context();
	free_context();
	exit(EXIT_FAILURE);
}
