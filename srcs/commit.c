/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:56:18 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/26 17:34:47 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "vector.h"
#include "push_swap.h"
#include <stdbool.h>

static bool	is_stack_a(t_stack_slice *slice, t_env *env)
{
	return (slice->stack == &env->a);
}

//Giving a non mergable op is UB
static t_ps_ops	merged_version(t_stack_ops op)
{
	if (op == ROTATE_UP)
		return (RR);
	if (op == ROTATE_DOWN)
		return (RRR);
	if (op == SWAP)
		return (SS);
	return (-1);
}

//TODO : handle SWAP_OR_ROTATE instructions if added
//Giving something like NO_COMMIT is UB
static t_ps_ops	single_version(t_stack_ops op, bool is_stack_a)
{
	if (op == SWAP && is_stack_a)
		return (SA);
	if (op == SWAP && !is_stack_a)
		return (SB);
	if (op == ROTATE_UP && is_stack_a)
		return (RA);
	if (op == ROTATE_UP && !is_stack_a)
		return (RB);
	if (op == ROTATE_DOWN && is_stack_a)
		return (RRA);
	if (op == ROTATE_DOWN && !is_stack_a)
		return (RRB);
	if (op == PUSH && is_stack_a)
		return (PB);
	if (op == PUSH && !is_stack_a)
		return (PA);
	return (-1);
}

bool	commit_moves(t_stack_slice *cur, t_stack_slice *other, t_env *env)
{
	bool	pushed;
	size_t	i;

	pushed = 0;
	i = 0;
	while (i < cur->ops->size && cur->ops->data[i] != STOP_COMMIT)
	{
		if (!pushed && cur->ops->data[i] != PUSH && other->ops->size
			&& other->ops->data[0] == cur->ops->data[i])
		{
			if (vector_append(&env->ps_ops, merged_version(cur->ops->data[i])))
				return (1);
		}
		else
			if (vector_append(&env->ps_ops, single_version(cur->ops->data[i],
						is_stack_a(cur, env))))
				return (1);
		if (cur->ops->data[i] == PUSH)
			pushed = true;
		i++;
	}
	vector_pop_n(cur->ops, 0, i + (i < cur->ops->size));
	return (0);
}
