/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 21:40:51 by kuibout           #+#    #+#             */
/*   Updated: 2020/01/22 10:58:30 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <pthread.h>

# include "libft_bitsize.h"
# include "clock.h"
# include "libft_conv.h"
# include "libft_vector.h"
# include "libft_gnl.h"
# include "libft_io.h"
# include "libft_lst.h"
# include "libft_map.h"
# include "libft_math.h"
# include "libft_mem.h"
# include "libft_str.h"
# include "ft_printf/ft_printf.h"

# ifdef __unix__
#  define INT32MAX __INT32_MAX__
# else
#  define INT32MAX INT32_MAX
# endif

#endif
