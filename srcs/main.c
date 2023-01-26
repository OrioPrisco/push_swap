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

int	main(int argc, char **argv)
{
	t_env			env;
	t_stack_slice	slice;
	t_vector		ops;
	t_vector		ops_b;
	t_stack_slice	slice_b;

	if (argc < 2)
		return (0);
	if (init_env(argc - 1, argv + 1, &env))
		return (1);
	vector_init(&ops);
	vector_init(&ops_b);
	slice = (t_stack_slice){&env.a, &ops, env.a.size, 0};
	slice_b = (t_stack_slice){&env.b, &ops_b, env.b.size, 0};
	if (split_stack(&slice, 0))
		return (destroy_env(&env), ft_printf("Allocation Error\n"), 1);
	print_stack_ops(slice.ops);
	commit_moves(&slice, &slice_b, &env);
	print_ps_ops(&env.ps_ops);
	commit_moves(&slice, &slice_b, &env);
	print_ps_ops(&env.ps_ops);
	vector_clear(&env.a);
	vector_clear(slice.ops);
	return (0);
}
