/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:21:22 by kguibout          #+#    #+#             */
/*   Updated: 2019/06/26 16:21:56 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include "libft.h"

typedef struct	s_line
{
	t_vec2i	d;
	t_vec2i	s;
	int		err;
	int		e2;
}				t_line;

#endif
