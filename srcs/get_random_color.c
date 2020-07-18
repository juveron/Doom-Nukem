/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_random_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 10:33:33 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/05 10:51:13 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_color	get_random_color(void)
{
	t_color	color;

	color = (rand() & 0xFE << 16) | (rand() & 0xFE << 8) | (rand() & 0xFE);
	return (color);
}
