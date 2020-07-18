/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 00:07:39 by kguibout          #+#    #+#             */
/*   Updated: 2018/12/20 13:23:12 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_u32	ft_size_str(t_u64 n, t_u32 base)
{
	t_u32	size_str;

	size_str = 1;
	if (base == 1)
		return (n);
	while (n >= base)
	{
		size_str++;
		n /= base;
	}
	return (size_str);
}

char			*ft_uitoa_base(t_u64 n, const char *base)
{
	t_u32	size_str;
	t_u32	size_base;
	char	*str;

	size_base = ft_strlen(base);
	size_str = ft_size_str(n, size_base);
	if (!(str = ft_strnew(size_str)))
		return (NULL);
	while (size_str--)
	{
		str[size_str] = base[n % size_base];
		n /= size_base;
	}
	return (str);
}
