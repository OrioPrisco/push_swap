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
#include "libft.h"
#include "ft_printf.h"
#include "sort.h"
#include "debug.h"
#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
		return (0);
	if (init_env(argc - 1, argv + 1, &env))
		return (1);
	if (sort3(&env.a, &env.stack_ops_a, 0))
		return (destroy_env(&env), ft_printf("Allocation Error\n"), 1);
	print_stack_ops(&env.stack_ops_a);
	vector_clear(&env.a);
	vector_clear(&env.stack_ops_a);
	return (0);
}
