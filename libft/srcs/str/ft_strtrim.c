/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 16:41:50 by kguibout          #+#    #+#             */
/*   Updated: 2018/12/18 10:50:52 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	end;
	size_t	len;
	char	*str;

	len = 0;
	i = 0;
	end = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[i + len])
	{
		if (s[i + len] == ' ' || s[i + len] == '\t' || s[i + len] == '\n')
			end++;
		else
			end = 0;
		len++;
	}
	len -= end;
	if ((str = ft_strnew(len)) == NULL)
		return (NULL);
	ft_strncpy(str, s + i, len);
	return (str);
}
