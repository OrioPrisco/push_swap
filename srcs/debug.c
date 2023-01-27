/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:09:34 by OrioPrisc         #+#    #+#             */
/*   Updated: 2023/01/23 18:58:11 by OrioPrisc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "vector.h"
#include "stack.h"
#include <stddef.h>

static const char	*g_stack_ops[] = {
	"ROTATE_UP",
	"ROTATE_DOWN",
	"PUSH",
	"SWAP",
	"STOP_COMMIT",
};

static const char	*g_ps_ops[] = {
	"SA",
	"SB",
	"SSS",
	"PA",
	"PB",
	"RA",
	"RB",
	"RR",
	"RRA",
	"RRB",
	"RRR",
};

void	print_stack_ops(const t_vector *ops)
{
	size_t	i;

	i = 0;
	while (i < ops->size)
	{
		ft_printf("%3d : %s\n", i, g_stack_ops[ops->data[i]]);
		i++;
	}
}

void	print_ps_ops(const t_vector *ops)
{
	size_t	i;

	i = 0;
	while (i < ops->size)
	{
		ft_printf("%3d : %s\n", i, g_ps_ops[ops->data[i]]);
		i++;
	}
}

void	print_stacks(const t_vector *a, const t_vector *b)
{
	size_t	i;

	i = 0;
	while (i < a->size || i < b->size)
	{
		ft_printf("+=======+=======+\n");
		if (i < a->size)
			ft_printf("| %5d ", a->data[i]);
		else
			ft_printf("|       ");
		if (i < b->size)
			ft_printf("| %5d |\n", b->data[i]);
		else
			ft_printf("|       |\n");
		i++;
	}
	ft_printf("+===A===+===B===+\n");
}
