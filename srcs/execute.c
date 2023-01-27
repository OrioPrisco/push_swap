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
static bool	execute_one(t_env *env, t_ps_ops op)
{
	if (op == SA)
		return (vector_insert(&env->a, 0, vector_pop(&env->a, 1)));
	if (op == SB)
		return (vector_insert(&env->b, 0, vector_pop(&env->b, 1)));
	if (op == SS)
		return (execute_one(env, SA) || execute_one(env, SB));
	if (op == PA)
		return (vector_insert(&env->a, 0, vector_pop(&env->b, 0)));
	if (op == PB)
		return (vector_insert(&env->b, 0, vector_pop(&env->a, 0)));
	if (op == RA)
		return (
			vector_insert(&env->a, env->a.size - 1, vector_pop(&env->a, 0)));
	if (op == RB)
		return (
			vector_insert(&env->b, env->b.size - 1, vector_pop(&env->b, 0)));
	if (op == RR)
		return (execute_one(env, RA) || execute_one(env, RB));
	if (op == RRA)
		return (
			vector_insert(&env->a, 0, vector_pop(&env->a, env->a.size - 1)));
	if (op == RRB)
		return (
			vector_insert(&env->b, 0, vector_pop(&env->b, env->b.size - 1)));
	return (execute_one(env, RRA) || execute_one(env, RRB));
}

bool	execute_ps_ops(t_env *env)
{
	while (env->ops_executed < env->ps_ops.size)
	{
		if (execute_one(env, env->ps_ops.data[env->ops_executed]))
			return (1);
		env->ops_executed++;
	}
	return (0);
}
