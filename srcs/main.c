/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 14:31:41 by thboura           #+#    #+#             */
/*   Updated: 2020/07/15 22:11:10 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	usage(void)
{
	ft_printf("Usage: ./doom-nukem [OPTION] [FILEPATH]\n\
	-n, --new\
		launch program without map (other arguments are not taken)\n\
	-v, --version\
		print supported map version (also verify if given map version \
is correct\n\
	-h, --help\
		show this usage\n");
	return (1);
}

static void	check_options(char **av, int ac)
{
	if (ft_strequ(av[1], "--help") || ft_strequ(av[1], "-h"))
		exit(usage());
	check_version_option(av, ac);
}

int			main(int ac, char **av)
{
	if (ac == 1)
		return (usage());
	else if (ac > 3)
		return (1);
	check_options(av, ac);
	if (!init_context())
		return (1);
	if (!init_3d_context())
		return (1);
	if (!app_run(av))
	{
		free_3d_context();
		free_context();
		return (1);
	}
	free_3d_context();
	free_context();
	return (0);
}
