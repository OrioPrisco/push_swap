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
#include <stddef.h>

static const char	*g_stack_ops[] = {
	"ROTATE_UP",
	"ROTATE_DOWN",
	"PUSH",
	"SWAP",
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
