/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 02:46:13 by kguibout          #+#    #+#             */
/*   Updated: 2019/12/16 02:49:44 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

/*
** Return dropped file path.
**
** !!! You need to duplicate this string because this pointer is fread every
** update !!!
**
** \return  string of the the dropped file, or NULL if no file are dropped.
*/

char	*get_dropped_file(void)
{
	return (get_context()->handle_event.drop.file_name);
}
