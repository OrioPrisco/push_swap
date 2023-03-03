/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_strats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:54:02 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/03/03 13:00:29 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "try.h"
#include "stack.h"
#include "vector.h"
#include <stdlib.h>

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
