/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 09:38:29 by kguibout          #+#    #+#             */
/*   Updated: 2019/06/26 13:05:41 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_H
# define TEXT_H

# include "libft.h"
# include "context.h"

SDL_Surface	*text_surface(char *text, int color, TTF_Font *font);

#endif
