/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_p3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 10:25:53 by kguibout          #+#    #+#             */
/*   Updated: 2019/12/16 08:27:43 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
** Return user input text.
**
** \return  string NULL terminated of the user input text
*/

char	*get_textinput(void)
{
	return (get_context()->handle_event.textinput.text);
}

t_vec2i	get_mouse_global_position(void)
{
	return (get_context()->handle_event.mouse_move.global_pos);
}
