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
	int			i;
	size_t		j;

	i = 1;
	vector_init(&vector);
	while (i < argc)
	{
		if (vector_append(&vector, ft_atoi(argv[i])))
			return (1);
		i++;
	}
	j = 0;
	while (j < vector.size)
	{
		ft_printf("[%d]\n", vector.data[j]);
		j++;
	}
	vector_clear(&vector);
	return (0);
}
