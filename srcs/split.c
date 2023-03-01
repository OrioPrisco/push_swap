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

static size_t	get_rot(const t_sub_stack *slice)
{
	if (slice->local_rot <= *slice->global_rot)
		return ((*slice->global_rot - slice->local_rot) % slice->stack->size);
	return (*slice->global_rot + slice->stack->size
		- (slice->local_rot - slice->stack->size));
}

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
	if ((slice->size > get_rot(slice) && vector_copy_n
			(&top, slice->stack->data, slice->size - get_rot(slice)))
		|| (get_rot(slice) && vector_copy_n(&bot, slice->stack->data
				+ (slice->stack->size - get_rot(slice)), get_rot(slice)))
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
	cur->size -= to_push;
	other->size += to_push;
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
	*cur->global_rot = (*cur->global_rot + rotated) % cur->stack->size;
	return (0);
}

//TODO : on reverse rotate, if the next elem also is to be pushed,
//		push the smallest first, by maybe delaying the push
//params : int[2] {median, to_push}
//FIXME : substraction at the end might be -1
static bool	split_down(t_sub_stack *cur, t_sub_stack *other, void *params)
{
	size_t	i;
	int		median;
	int		to_push;
	size_t	rotated;

	median = ((int *)params)[0];
	to_push = ((int *)params)[1];
	i = cur->stack->size;
	cur->size -= to_push;
	other->size += to_push;
	rotated = 0;
	while (to_push)
	{
		if ((cur->stack->data[i-- % cur->stack->size] < median) ^ cur->reversed)
		{
			if ((to_push--, vector_append(cur->ops, PUSH)) || (to_push
						&& (rotated++, vector_append(cur->ops, ROTATE_DOWN))))
				return (1);
		}
		else if (rotated ++, vector_append(cur->ops, ROTATE_DOWN))
			return (1);
	}
	*cur->global_rot = (*cur->global_rot - rotated) % cur->stack->size;
	return (0);
}

bool	split_up_down(t_sub_stack *cur, t_sub_stack *other, void *params_)
{
	int				*params;
	t_sub_stacks	*try;
	t_vector		ops;

	params = params_;
	try = try_strat(cur, other, split_up, params);
	vector_init(&ops);
	if (!try)
		return (1);
	if (vector_append_elems(cur->ops, try->cur.ops->data, try->cur.ops->size)
		|| translate_stack_ops(&try->cur, &try->other, &ops)
		|| (cur->is_a && execute_ps_ops(try->cur.stack, try->other.stack,
				&ops, NULL))
		|| (!cur->is_a && execute_ps_ops(try->other.stack, try->cur.stack,
				&ops, NULL))
		|| split_down(&try->cur, &try->other, params + 2)
		|| vector_append_elems(cur->ops, try->cur.ops->data, try->cur.ops->size)
	)
		return (free(destroy_sub_stacks(try)), vector_clear(&ops), 1);
	cur->size = try->cur.size;
	*cur->global_rot = *try->cur.global_rot;
	other->size = try->other.size;
	*other->global_rot = *try->other.global_rot;
	other->local_rot = *other->global_rot;
	return (free(destroy_sub_stacks(try)), 0);
}

bool	split_down_up(t_sub_stack *cur, t_sub_stack *other, void *params_)
{
	int				*params;
	t_sub_stacks	*try;
	t_vector		ops;

	params = params_;
	try = try_strat(cur, other, split_down, params + 2);
	vector_init(&ops);
	if (!try)
		return (1);
	if (vector_append_elems(cur->ops, try->cur.ops->data, try->cur.ops->size)
		|| translate_stack_ops(&try->cur, &try->other, &ops)
		|| (cur->is_a && execute_ps_ops(try->cur.stack, try->other.stack,
				&ops, NULL))
		|| (!cur->is_a && execute_ps_ops(try->other.stack, try->cur.stack,
				&ops, NULL))
		|| split_up(&try->cur, &try->other, params)
		|| vector_append_elems(cur->ops, try->cur.ops->data, try->cur.ops->size)
	)
		return (free(destroy_sub_stacks(try)), vector_clear(&ops), 1);
	cur->size = try->cur.size;
	*cur->global_rot = *try->cur.global_rot;
	other->size = try->other.size;
	*other->global_rot = *try->other.global_rot;
	other->local_rot = *other->global_rot;
	return (free(destroy_sub_stacks(try)), 0);
}

static t_f_triable *const	g_strats[] = {
	split_up_down,
	split_down_up,
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
	other->size = 0;
	best = best_strat(cur, other, &g_split_strats, &params[0]);
	if (!best)
		return (1);
	move_substack(cur, &best->cur);
	move_substack(other, &best->other);
	other->reversed = !cur->reversed;
	free(best);
	return (0);
}
