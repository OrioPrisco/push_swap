/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:03:26 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/02/14 17:48:27 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"
#include "vector.h"
#include "try.h"
#include <stdlib.h>
#include "libft.h"

//TODO : consider sortedness
bool	score(t_sub_stacks *slice, size_t *result)
{
	t_sub_stacks	copies;
	t_vector		ops;

	cancel_ops(slice->cur.ops, 1);
	cancel_ops(slice->other.ops, 1);
	vector_init(&ops);
	if (copy_sub_stack(&copies.cur, &slice->cur)
		|| copy_sub_stack(&copies.other, &slice->other)
		|| translate_stack_ops(&copies.cur, &copies.other, &ops)
		|| (cancel_ops(&ops, 0), merge_ops(&ops), 0))
		return (destroy_sub_stacks(&copies), vector_clear(&ops), 1);
	*result = ops.size - (slice->other.ops->size - copies.other.ops->size);
	return (destroy_sub_stacks(&copies), vector_clear(&ops), 0);
}

bool	keep_best(t_sub_stacks *current, t_sub_stacks **best)
{
	size_t	scores[2];

	cancel_ops(current->cur.ops, 1);
	cancel_ops((*best)->cur.ops, 1);
	if (score(current, &scores[0]) || score(*best, &scores[1]))
		return (1);
	if (scores[0] < scores[1])
	{
		free(destroy_sub_stacks(*best));
		*best = current;
	}
	else
		free(destroy_sub_stacks(current));
	return (0);
}

t_sub_stacks	*try_strat(const t_sub_stack *cur, const t_sub_stack *other,
	t_f_triable *strat, void *params)
{
	t_sub_stacks	*copies;
	bool			error;

	copies = malloc(sizeof(*copies));
	if (!copies)
		return (0);
	ft_bzero(copies, sizeof(*copies));
	error = (copy_sub_stack(&copies->cur, cur) || copy_sub_stack(&copies->other,
				other) || strat(&copies->cur, &copies->other, params));
	if (error)
	{
		free(destroy_sub_stacks(copies));
		return (0);
	}
	return (copies);
}

t_sub_stacks	*best_strat(const t_sub_stack *cur, const t_sub_stack *other,
	const t_funcs *strats, void *param)
{
	t_sub_stacks	*best;
	t_sub_stacks	*current;
	size_t			i;

	if (strats->size == 0)
		return (0);
	best = try_strat(cur, other, strats->strats[0], param);
	if (!best)
		return (0);
	i = 1;
	while (i < strats->size)
	{
		current = try_strat(cur, other, strats->strats[i], param);
		if (!current)
			return (free(destroy_sub_stacks(best)), NULL);
		if (keep_best(current, &best))
			return (free(destroy_sub_stacks(best)),
				free(destroy_sub_stacks(current)), NULL);
		i++;
	}
	return (best);
}
