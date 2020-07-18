/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 01:10:04 by marvin            #+#    #+#             */
/*   Updated: 2019/11/12 10:58:08 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset_fast(void *s, int c, size_t n)
{
	unsigned char			*cp;
	t_u64					*lp;
	t_u64					word;

	cp = s;
	c = c & 0xFF;
	while (n && (((t_u64)cp & (sizeof(t_u64) - 1)) != 0))
	{
		*(cp++) = (unsigned char)c;
		n--;
	}
	lp = (t_u64 *)((void *)cp);
	word = (t_u64)c << 24 | (t_u64)c << 16 | (t_u64)c << 8 | (t_u64)c;
	word = word << 32 | word;
	while (n > sizeof(t_u64))
	{
		*(lp++) = word;
		n -= sizeof(t_u64);
	}
	cp = (unsigned char *)((void *)lp);
	while (n--)
		*(cp++) = (unsigned char)c;
	return (s);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char			*cp;

	cp = s;
	while (n--)
		*(cp++) = (unsigned char)c;
	return (s);
}
