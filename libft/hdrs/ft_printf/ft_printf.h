/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:42:49 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/06 12:44:52 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

int		ft_printf(const char *format,
		...) __attribute__((format(printf,1,2)));
int		ft_asprintf(char **ret, const char *format,
		...) __attribute__((format(printf,2,3)));
int		ft_dprintf(int fd, const char *format,
		...) __attribute__((format(printf,2,3)));
int		ft_snprintf(char *ret, size_t size, const char *format,
		...) __attribute__((format(printf,3,4)));

#endif
