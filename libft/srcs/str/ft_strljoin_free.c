/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:00:16 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 21:30:44 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(size_t size, char *s1, char *s2)
{
	size_t	size_str;
	char	*str;

	size_str = ft_strlen(s1) + ft_strlen(s2);
	if (size_str + 1 > size)
	{
		if ((str = (char *)malloc(size)) == NULL)
			return (NULL);
	}
	else
	{
		if ((str = (char *)malloc(size_str + 1)) == NULL)
			return (NULL);
	}
	ft_strlcpy(str, s1, size);
	ft_strlcat(str, s2, size);
	return (str);
}

char		*ft_strljoin_free(char *s1, char *s2, t_u8 num_param,
	size_t size)
{
	char	*str;

	str = NULL;
	if (s1 != NULL && s2 != NULL)
		str = join(size, s1, s2);
	else if (s1 != NULL)
	{
		if (ft_strlen(s1) + 1 > size)
			str = ft_strsub(s1, 0, size);
		else
			str = ft_strdup(s1);
	}
	else if (s2 != NULL)
	{
		if (ft_strlen(s2) + 1 > size)
			str = ft_strsub(s2, 0, size);
		else
			str = ft_strdup(s2);
	}
	if (num_param == 1 || num_param == 3)
		free(s1);
	if (num_param == 2 || num_param == 3)
		free(s2);
	return (str);
}
