/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:21:30 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/27 14:56:25 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "vector.h"

//passing invalid PS op is UB
static bool	execute_one(t_vector *a, t_vector *b, t_ps_ops op)
{
	if (op == SA)
		return (vector_insert(a, 0, vector_pop(a, 1)));
	if (op == SB)
		return (vector_insert(b, 0, vector_pop(b, 1)));
	if (op == SS)
		return (execute_one(a, b, SA) || execute_one(a, b, SB));
	if (op == PA)
		return (vector_insert(a, 0, vector_pop(b, 0)));
	if (op == PB)
		return (vector_insert(b, 0, vector_pop(a, 0)));
	if (op == RA)
		return (vector_append(a, vector_pop(a, 0)));
	if (op == RB)
		return (vector_append(b, vector_pop(b, 0)));
	if (op == RR)
		return (execute_one(a, b, RA) || execute_one(a, b, RB));
	if (op == RRA)
		return (vector_insert(a, 0, vector_pop(a, a->size - 1)));
	if (op == RRB)
		return (vector_insert(b, 0, vector_pop(b, b->size - 1)));
	return (execute_one(a, b, RRA) || execute_one(a, b, RRB));
}

bool	execute_ps_ops(t_vector *a, t_vector *b, t_vector *ops,
	size_t *ops_executed)
{
	size_t	ops_exed;

	ops_exed = 0;
	if (!ops_executed)
		ops_executed = &ops_exed;
	while (*ops_executed < ops->size)
	{
		if (execute_one(a, b, ops->data[*ops_executed]))
			return (1);
		++(*ops_executed);
	}
	return (0);
}

bool	execute_ps_ops_env(t_env *env)
{
	return (execute_ps_ops(&env->a, &env->b, &env->ps_ops, &env->ops_executed));
}
