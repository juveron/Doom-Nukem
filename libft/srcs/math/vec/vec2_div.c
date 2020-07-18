/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:17:51 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/12 16:58:45 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec2i		vec2i_div(t_vec2i vec1, int div)
{
	return ((t_vec2i){vec1.x / div, vec1.y / div});
}

t_vec2ui	vec2ui_div(t_vec2ui vec1, t_u32 div)
{
	return ((t_vec2ui){vec1.x / div, vec1.y / div});
}

t_vec2f		vec2f_div(t_vec2f vec1, float div)
{
	return ((t_vec2f){vec1.x / div, vec1.y / div});
}

t_vec2d		vec2d_div(t_vec2d vec1, double div)
{
	return ((t_vec2d){vec1.x / div, vec1.y / div});
}
