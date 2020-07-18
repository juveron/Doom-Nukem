/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component_p2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 16:42:03 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/17 17:39:46 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void	component_add_background_image(void *component, SDL_Surface *surface)
{
	t_component	*comp;

	comp = component;
	comp->background_image = surface;
	comp->use_background = true;
}
