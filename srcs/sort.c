/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:03:53 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/30 16:23:18 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "stack.h"
#include "push_swap.h"
#include "sort.h"
#include "ft_printf.h"

bool	merge_stacks(t_sub_stack *dest, t_sub_stack *src)
{
	if (dest->reversed == src->reversed)
	{
		ft_printf("Merging unreversed stacks slices is not implemented !\n");
		return (1);
	}
	if (vector_append_n(src->ops, PUSH, src->size))
		return (1);
	return (0);
}

//TODO : after everything is sorted, do passes to remove instructions cancelling
//		each other, like pa pb, ra rra, or ra rb rra (rb has no influence on a)
//		maybe do passes when translating too
bool	sort_stacks(t_sub_stack cur, t_sub_stack other, t_env *env)
{
	t_vector	cur_ops;
	size_t		pushed;

	vector_init(&cur_ops);
	cur.ops = &cur_ops;
	if (cur.size <= 3)
		return ((sort3(&cur) || translate_stack_ops
				(&cur, &other, env) || (vector_clear(&cur_ops), 0)
				|| execute_ps_ops(env)) && (vector_clear(&cur_ops), 1));
	if (split_stack(&cur, &other, &cur.rotated, &pushed)
		|| translate_stack_ops(&cur, &other, env) || execute_ps_ops(env))
		return (vector_clear(&cur_ops), 1);
	cur.size -= pushed;
	other = (t_sub_stack){other.stack, other.ops, pushed, 0, !cur.reversed};
	if (unrotate(&cur, &other) || translate_stack_ops(&cur, &other, env)
		|| execute_ps_ops(env))
		return (vector_clear(&cur_ops), 1);
	cur.rotated = 0;
	if (sort_stacks(cur, other, env) || sort_stacks(other, cur, env)
		|| merge_stacks(&cur, &other) || translate_stack_ops(&cur, &other, env)
		|| translate_stack_ops(&other, &cur, env) || execute_ps_ops(env))
		return (vector_clear(&cur_ops), 1);
	cur.size += pushed;
	return (vector_clear(&cur_ops), 0);
}
