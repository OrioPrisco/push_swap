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

int	main(int argc, char **argv)
{
	t_vector	vector;
	t_vector	stack_ops;
	int			i;

	i = 1;
	vector_init(&vector);
	vector_init(&stack_ops);
	while (i < argc)
	{
		if (vector_append(&vector, ft_atoi(argv[i])))
			return (1);
		i++;
	}
	if (sort3(&vector, &stack_ops, 0))
		return (1);
	print_stack_ops(&stack_ops);
	vector_clear(&vector);
	vector_clear(&stack_ops);
	return (0);
}
