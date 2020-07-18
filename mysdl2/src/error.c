/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 03:05:13 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:08:57 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include <stdio.h>

t_u64	sdl_throw_error(char *msg, int ret_val, bool exit_val)
{
	ft_dprintf(2, "%s -> (%s)\n", msg, SDL_GetError());
	free_context();
	if (exit_val)
		exit(ret_val);
	else
		return (ret_val);
}
