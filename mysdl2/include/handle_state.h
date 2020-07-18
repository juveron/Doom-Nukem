/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:49:49 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 11:07:16 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_STATE_H
# define HANDLE_STATE_H

# include "libft.h"

typedef t_vector	t_state_stack;

typedef struct		s_state_handle
{
	void	(*init)(void *);
	void	(*draw)(void *);
	void	(*update)(void *);
	void	(*destroy)(void *);
	void	*param;
}					t_state_handle;

void				push_state(t_state_stack *stack, t_state_handle *state);
void				pop_state(t_state_stack *stack);
t_state_handle		*create_state(void (*draw)(void *), void (*update)(void *),
	void (*init)(void *), void	(*destroy)(void *));
void				update_state(t_state_stack *stack);
void				state_add_param(t_state_handle *state, void *param);
void				delete_state(t_state_handle **state);
bool				init_state_stack(t_state_stack *state);

#endif
