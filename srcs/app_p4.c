/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_p4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:12:59 by thboura           #+#    #+#             */
/*   Updated: 2020/07/15 22:13:39 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "fcntl.h"

static bool	init_map(t_env *env)
{
	if (!(env->current_map = create_map("map 1"))
		|| !vector_push(&env->maps, &env->current_map)
		|| !(env->map_file.file_name = ft_strdup("default name")))
		return (false);
	return (true);
}

void		check_new_map_option(char *option, t_env *env)
{
	if (ft_strequ(option, "--new") || ft_strequ(option, "-n"))
		env->test_mode = true;
	if (env->test_mode && !init_map(env))
		throw_error("DOOM_NUKEM: Fail to init map.", env);
}

static bool	check_file_name(char *path)
{
	char	*name;

	if (!(name = get_file_name(path)))
		return (false);
	free(name);
	return (true);
}

void		check_map_version(char **av)
{
	int		fd;
	char	buff[32];
	char	*version;

	if ((fd = open(av[2], O_RDONLY)) == -1)
		exit(EXIT_FAILURE);
	if (read(fd, buff, sizeof(buff)) < (long)(4 + sizeof(MAP_VERSION)))
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (!(version = ft_strnew(4 + sizeof(MAP_VERSION))))
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	ft_strncpy(version, buff + 4, 4 + sizeof(MAP_VERSION));
	ft_printf("Map version: %s\n", version);
	if (ft_strequ(version, MAP_VERSION))
		ft_printf("{green}This map version is currently supported{end}\n");
	else
		ft_printf("{red}This map version is not supported{end}\n");
	free(version);
	close(fd);
}

void		check_version_option(char **av, int ac)
{
	if (ft_strequ(av[1], "--version") || ft_strequ(av[1], "-v"))
	{
		ft_printf("Current map version: %s\n", MAP_VERSION);
		if (ac == 3)
			if (check_file_name(av[2]))
				check_map_version(av);
		exit(EXIT_SUCCESS);
	}
}
