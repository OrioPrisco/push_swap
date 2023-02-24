/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:16:12 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/18 17:16:55 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "stack.h"
#include "libft.h"
#include "ft_printf.h"
#include "sort.h"
#include "debug.h"
#include "push_swap.h"

static void	init_substack(t_sub_stack *substack, t_vector *ops, t_env *env,
	bool is_a)
{
	vector_init(ops);
	if (is_a)
		*substack = (t_sub_stack){&env->a, ops, env->a.size, &env->rot_a, 0, 1};
	else
		*substack = (t_sub_stack){&env->b, ops, env->b.size, &env->rot_b, 0, 0};
}

int	main(int argc, char **argv)
{
	t_env			env;
	t_sub_stack		slice;
	t_vector		ops;
	t_vector		ops_b;
	t_sub_stack		slice_b;

	if (argc < 2)
		return (0);
	if (init_env(argc - 1, argv + 1, &env))
		return (1);
	init_substack(&slice, &ops, &env, true);
	init_substack(&slice_b, &ops_b, &env, false);
	if (sort_stacks(slice, slice_b, &env) || (cancel_ops(&env.ps_ops, 0),
			merge_ops(&env.ps_ops), 0))
		ft_printf("error !\n");
	if (!OUTPUT_DBG)
		output_ps_ops(&env.ps_ops);
	vector_clear(&env.a);
	vector_clear(&env.b);
	vector_clear(slice.ops);
	vector_clear(slice_b.ops);
	vector_clear(&env.ps_ops);
	return (0);
}
