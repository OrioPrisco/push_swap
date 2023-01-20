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

int	main(int argc, char **argv)
{
	t_vector	vector;
	t_vector	vector2;
	int			i;

	i = 1;
	vector_init(&vector);
	while (i < argc)
	{
		if (vector_insert(&vector, 0, ft_atoi(argv[i])))
			return (1);
		i++;
	}
	if (vector_copy(&vector2, &vector))
		return (vector_clear(&vector), 1);
	vector_sort(&vector2);
	while (vector.size)
	{
		ft_printf("[%5d] [%5d]\n", vector_pop(&vector2, 0),
			vector_pop(&vector, 0));
	}
	vector_clear(&vector);
	vector_clear(&vector2);
	return (0);
}
