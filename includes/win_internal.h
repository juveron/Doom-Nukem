/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 10:18:15 by thboura           #+#    #+#             */
/*   Updated: 2020/07/15 03:03:08 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIN_INTERNAL_H
# define WIN_INTERNAL_H

# include "doom_nukem.h"

bool	set_highscore(t_env *env);
bool	resume_win_menu(void *param);
bool	main_menu_win_menu(void *param);
bool	exit_win_menu(void *param);

#endif
