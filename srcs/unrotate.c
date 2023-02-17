/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unrotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:29:32 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/02/02 19:30:07 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stack.h"
#include "vector.h"
#include "try.h"
#include <stdlib.h>
#include "ft_printf.h"

//TODO : Determine best way to unrotate
//TODO : Use rotate-or-swap if possible ?

bool	rotate_down_to(t_sub_stack *cur, t_sub_stack *other, void *param)
{
	size_t	destination;

	(void)other;
	destination = *(size_t *)param;

	if (cur->rotated > destination)
	{
		if (vector_append_n(cur->ops, ROTATE_DOWN, cur->rotated - destination))
			return (1);
	}
	else if (vector_append_n(cur->ops, ROTATE_DOWN,
			cur->stack->size - (cur->rotated - destination)))
		return (1);
	cur->rotated = destination;
	return (0);
}

bool	rotate_up_to(t_sub_stack *cur, t_sub_stack *other, void *param)
{
	size_t	destination;

	(void)other;
	destination = *(size_t *)param;

	if (cur->rotated < destination)
	{
		if (vector_append_n(cur->ops, ROTATE_UP, destination - cur->rotated))
			return (1);
	}
	else if (vector_append_n(cur->ops, ROTATE_UP,
			cur->stack->size - (destination - cur->rotated)))
		return (1);
	cur->rotated = destination;
	return (0);
}

static t_f_triable *const	g_strats[] = {
	rotate_down_to,
	rotate_up_to,
};

static const t_funcs		g_rotate_strats = {
	&g_strats[0],
	sizeof(g_strats) / sizeof(*g_strats)
};

bool	rotate_to(t_sub_stack *cur, t_sub_stack *other, void *destination)
{
	t_sub_stacks	*best;
	size_t			dest;

	dest = *(size_t *)destination;
	if (dest == cur->rotated)
		return (0);
	best = best_strat(cur, other, &g_rotate_strats, destination);
	if (!best)
		return (1);
	move_substack(cur, &best->cur);
	move_substack(other, &best->other);
	free(best);
	return (0);
}

bool	unrotate(t_sub_stack *cur, t_sub_stack *other, void *_)
{
	size_t	zero;

	zero = 0;
	(void)_;
	if (OUTPUT_DBG)
		ft_printf("unrotating by %d\n", cur->rotated);
	if (cur->size == cur->stack->size)
	{
		cur->rotated = 0;
		return (0);
	}
	return (rotate_to(cur, other, &zero));
}
