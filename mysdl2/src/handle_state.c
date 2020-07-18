/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:29:58 by kguibout          #+#    #+#             */
/*   Updated: 2019/07/19 12:46:54 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_state.h"
#include "libft.h"
#include "context.h"

/*
** Update the current state.
**
** \param   stack Pointer on the state stack
*/

void			update_state(t_state_stack *stack)
{
	t_state_handle	*state;

	state = vector_back(stack);
	state->update(state->param);
	state->draw(state->param);
}

/*
** Create new state.
**
** \param   draw  Pointer to the draw function
** \param   update  Pointer to the update function
** \param   init  Pointer to the init function
** \param   destroy  Pointer to the destroy function
**
** \return  Pointer to the new state
*/

t_state_handle	*create_state(void (*draw)(void *), void (*update)(void *),
	void (*init)(void *), void (*destroy)(void *))
{
	t_state_handle	*state;

	if (!(state = (t_state_handle *)malloc(sizeof(t_state_handle))))
		return (NULL);
	state->draw = draw;
	state->update = update;
	state->init = init;
	state->destroy = destroy;
	state->param = NULL;
	return (state);
}

/*
** Add parameter to the state.
**
** \param   state  Pointer to the state
** \param   param Pointer to the parameter
*/

void			state_add_param(t_state_handle *state, void *param)
{
	state->param = param;
}

/*
** Delete the state.
**
** \param   draw  Pointer to the pointer of the state
*/

void			delete_state(t_state_handle **state)
{
	ft_memdel((void **)state);
}

/*
** Push the state on the stack and call his init function.
**
** \param   stack  Pointer to the state stack
** \param   state  Pointer to the state
*/

void			push_state(t_state_stack *stack, t_state_handle *state)
{
	state->init(state->param);
	vector_push(stack, state);
}
