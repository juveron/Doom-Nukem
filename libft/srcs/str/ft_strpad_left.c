/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:09:32 by kguibout          #+#    #+#             */
/*   Updated: 2018/12/18 16:09:40 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpad_left(const char *s, char const c, t_u32 n)
{
	t_u32	i;
	t_u32	len;
	char	*result;

	if (!s)
		return (NULL);
	len = n + ft_strlen(s);
	if (!(result = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = c;
		++i;
	}
	ft_strlcpy(result + i, s, ft_strlen(s) + 1);
	return (result);
}
