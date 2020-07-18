/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:41:17 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 12:29:58 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_part_lst(char **lst_fd)
{
	ft_memdel((void **)lst_fd);
	return (0);
}

static int	get_new_line(char **str, char **line)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\n')
	{
		if (!(*line = ft_strsub(*str, 0, len)))
			return (-1);
		(*line)[len] = 0;
		if (!(tmp = ft_strdup(*str + len + 1)))
			return (-1);
		free(*str);
		*str = tmp;
	}
	else if ((*str)[len] == '\0')
	{
		if (!(*line = ft_strdup(*str)))
			return (-1);
		ft_strdel(str);
	}
	return (1);
}

static int	free_all_data(char **fd)
{
	int	i;

	i = 0;
	while (i < 512)
	{
		ft_strdel(&fd[i]);
		++i;
	}
	return (0);
}

static int	get_line(char **lst_fd, int fd, int *ret)
{
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	while (!(ft_strchr(lst_fd[fd], '\n'))
		&& (*ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[*ret] = '\0';
		if (!(tmp = ft_strjoin(lst_fd[fd], buffer)))
			return (0);
		free(lst_fd[fd]);
		lst_fd[fd] = tmp;
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	static char		*lst_fd[512];

	ret = 1;
	if (fd == -2)
		return (free_all_data(lst_fd));
	if (fd < 0 || line == NULL)
		return (-1);
	if (!lst_fd[fd])
		lst_fd[fd] = (char *)ft_memalloc(1);
	if (!get_line(lst_fd, fd, &ret))
		return (-1);
	if (ret < 0)
		return (-1);
	if (!ret && (!lst_fd[fd] || !*lst_fd[fd]))
		return (free_part_lst(&lst_fd[fd]));
	return (get_new_line(&lst_fd[fd], line));
}
