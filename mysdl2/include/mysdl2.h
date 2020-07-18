/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysdl2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:26:43 by kguibout          #+#    #+#             */
/*   Updated: 2019/12/16 02:50:28 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSDL2_H
# define MYSDL2_H

# include <SDL2/SDL.h>
# include "text.h"
# include "context.h"
# include "event.h"
# include "input.h"
# include "draw.h"
# include "pixel.h"
# include "handle_state.h"
# include "bmp.h"
# include "tga.h"
# include "draw3d.h"

char	*get_dropped_file(void);

#endif
