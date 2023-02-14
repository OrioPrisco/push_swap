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

bool	copy_sub_stack(t_sub_stack *dest, const t_sub_stack *src)
{
	*dest = *src;
	dest->stack = malloc(sizeof(*dest->stack));
	dest->ops = malloc(sizeof(*dest->ops));
	if (!dest->stack || ! dest->ops)
	{
		free(dest->stack);
		free(dest->ops);
		return (1);
	}
	if (vector_copy(dest->stack, src->stack)
		|| vector_copy(dest->ops, src->ops))
	{
		free(vector_clear(dest->stack));
		free(vector_clear(dest->ops));
		return (1);
	}
	return (0);
}

t_sub_stacks	*destroy_sub_stacks(t_sub_stacks *stacks)
{
	free(vector_clear(stacks->cur.stack));
	free(vector_clear(stacks->cur.ops));
	free(vector_clear(stacks->other.stack));
	free(vector_clear(stacks->other.ops));
	return (stacks);
}

//is it truly necessary to move the stacks ?
//I don't think I'm gonna try something that commts move...
//same for the other properties
t_sub_stack	*move_substack(t_sub_stack *dest, t_sub_stack *src)
{
	vector_copy(vector_clear(dest->ops), src->ops);
	vector_copy(vector_clear(dest->stack), src->stack);
	free(vector_clear(src->ops));
	free(vector_clear(src->stack));
	dest->size = src->size;
	dest->rotated = src->rotated;
	dest->reversed = src->reversed;
	dest->is_a = src->is_a;
	return (dest);
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

//TODO : translate to get a better idea of which is best
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
		if (current->cur.ops->size < best->cur.ops->size)
		{
			free(destroy_sub_stacks(best));
			best = current;
		}
		else
			free(destroy_sub_stacks(current));
		i++;
	}
	return (best);
}
