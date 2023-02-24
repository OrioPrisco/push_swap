/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:50:17 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/26 15:16:45 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "order.h"
#include "stack.h"
#include "push_swap.h"
#include "try.h"
#include <stdbool.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

//TODO: push smallest # of elems ?/ push elems%3 if size is 4 or 5
//calculates parameters for splitting
//{median, to_push_top, median, to_push_bot}
static bool	get_params(int *params, const t_sub_stack *slice)
{
	t_vector	top;
	t_vector	bot;
	t_vector	all;
	size_t		i;

	if (vector_init(&top), vector_init(&bot), vector_init(&all), 0)
		return (1);
	if ((slice->size > *slice->rotated && vector_copy_n
			(&top, slice->stack->data, slice->size - *slice->rotated))
		|| (slice->rotated && vector_copy_n(&bot, slice->stack->data
				+ (slice->stack->size - *slice->rotated), *slice->rotated))
		|| vector_copy(&all, &top)
		|| vector_append_elems(&all, bot.data, bot.size))
		return (vector_clear(&all), vector_clear(&top), vector_clear(&bot), 1);
	vector_sort(&all);
	ft_bzero(params, 4 * sizeof(*params));
	params[0] = all.data[(all.size / 2)];
	params[2] = all.data[(all.size / 2)];
	i = -1;
	while (++i < top.size)
		((top.data[i] < params[0]) ^ slice->reversed) && params[1]++;
	i = -1;
	while (++i < bot.size)
		((bot.data[i] < params[2]) ^ slice->reversed) && params[3]++;
	return (vector_clear(&all), vector_clear(&top), vector_clear(&bot), 0);
}

//TODO : for the last rotate put a ROTATE_OR_SWAP, and let commit fct
//		decide what op to translate into
//		/!\unrotating is now left to the sorter, allowing to decouple the split
//		and rotate logic
//params : int[2] {median, to_push}
static bool	split_up(t_sub_stack *cur, t_sub_stack *other, void *params)
{
	size_t	rotated;
	size_t	i;
	int		median;
	int		to_push;

	median = ((int *)params)[0];
	to_push = ((int *)params)[1];
	i = 0;
	rotated = 0;
	other->size = to_push;
	cur->size -= to_push;
	while (to_push)
	{
		if ((cur->stack->data[i++] < median) ^ cur->reversed)
		{
			if (to_push--, vector_append(cur->ops, PUSH))
				return (1);
		}
		else if (rotated++, vector_append(cur->ops, ROTATE_UP))
			return (1);
	}
	*cur->rotated = rotated;
	other->reversed = !cur->reversed;
	return (0);
}

//TODO : on reverse rotate, if the next elem also is to be pushed,
//		push the smallest first, by maybe delaying the push
//params : int[2] {median, to_push}
static bool	split_down(t_sub_stack *cur, t_sub_stack *other, void *params)
{
	size_t	i;
	int		median;
	int		to_push;

	median = ((int *)params)[0];
	to_push = ((int *)params)[1];
	i = 0;

	cur->size -= (other->size = to_push);
	while (to_push)
	{
		if ((cur->stack->data[i] < median) ^ cur->reversed)
		{
			if ((to_push--, vector_append(cur->ops, PUSH))
				|| (to_push && vector_append(cur->ops, ROTATE_DOWN)))
				return (1);
		}
		else if (vector_append(cur->ops, ROTATE_DOWN))
			return (1);
		if (i-- == 0)
			i = cur->stack->size - 1;
	}
	*cur->rotated = 0;// # of ROTATE - # of PUSH after the first ROTATE
	other->reversed = !cur->reversed;
	return (0);
}

/*
//TODO get median for each one
bool	split_up_down(t_sub_stack *cur, t_sub_stack *other, void *params_)
{
	int	*params;
	params = params_;
	return (split_up(cur, other, params) )
}
//TODO get median for each one
bool	split_down_up(t_sub_stack *cur, t_sub_stack *other, void *params)
{
	t_sub_stacks	*copy;
	t_vector		temp;

	copy = try_strat(cur, other, unrotate, NULL);
	if (!copy)
		return (1);
	if (vector_copy(vector_clear(cur->ops), copy->cur.ops)
		|| translate_stack_ops(&copy->cur, &copy-> other, vector_init(&temp))
		|| execute_ps_ops(copy->cur.ops, copy->other.ops, &temp, NULL)
		|| split_up(&copy->cur, &copy->other, params))
		return (1);
	return (vector_append_elems
		(cur->ops, copy->cur.ops->data, copy->cur.ops->size));
}
*/

static t_f_triable *const	g_strats[] = {
	split_up,
	split_down,
};

static const t_funcs		g_split_strats = {
	&g_strats[0],
	sizeof(g_strats) / sizeof(*g_strats)
};

//modifies other such that the size and rotated will be accurate
//once ops are translated and executed
//does not clear the instructions vector however
bool	split_stack(t_sub_stack *cur, t_sub_stack *other, void *_)
{
	t_sub_stacks	*best;
	int				params[4];

	(void)_;
	if (get_params(&params[0], cur))
		return (1);
	if (OUTPUT_DBG)
		ft_printf("splitting %u (%u/%u)\n", params[1], cur->size,
			cur->stack->size);
	best = best_strat(cur, other, &g_split_strats, &params[0]);
	if (!best)
		return (1);
	move_substack(cur, &best->cur);
	move_substack(other, &best->other);
	free(best);
	return (0);
}
