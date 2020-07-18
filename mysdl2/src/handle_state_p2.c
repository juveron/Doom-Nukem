/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 12:46:34 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 15:44:08 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_state.h"
#include "libft.h"
#include "context.h"

/*
** Pop state from the stack and call his destoy function.
**
** \param  stack Pointer on the state stack
*/

void	pop_state(t_state_stack *stack)
{
	t_state_handle	*state;

	state = vector_back(stack);
	state->destroy(state->param);
	vector_pop(stack);
}

/*
** Init state stack.
**
** \param  stack Pointer on the state stack
*/

bool	init_state_stack(t_state_stack *state)
{
	return (vector_init(state, sizeof(t_state_handle)));
}
