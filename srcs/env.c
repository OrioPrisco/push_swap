/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:24:16 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/24 18:55:00 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "push_swap.h"
#include "libft.h"
#include "ft_printf.h"

static int	duplicates(t_vector *vec)
{
	t_vector	sorted;
	size_t		i;

	if (vec->size < 2)
		return (0);
	vector_copy(&sorted, vec);
	vector_sort(&sorted);
	i = 0;
	while (i < sorted.size - 1)
	{
		if (sorted.data[i] == sorted.data[i + 1])
			return (ft_printf("Duplicate Value : %d\n", sorted.data[i]));
		i++;
	}
	return (0);
}

int	init_env(int argc, char **argv, t_env *env)
{
	char	*endptr;
	int		nbr;
	int		i;

	i = 0;
	ft_bzero(env, sizeof(*env));
	while (i < argc)
	{
		nbr = ft_strtol(argv[i], &endptr, 10);
		if (*endptr)
			return (ft_printf
				("Error parsing argument #%d %s\n", i, argv[i]));
		if (vector_append(&env->a, nbr))
			return (1);
		i++;
	}
	return (duplicates(&env->a));
}

void	destroy_env(t_env *env)
{
	vector_clear(&env->a);
	vector_clear(&env->b);
	vector_clear(&env->ps_ops);
}
