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
#include "mod.h"

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
	"SS",
	"PA",
	"PB",
	"RA",
	"RB",
	"RR",
	"RRA",
	"RRB",
	"RRR",
};

static const char	*g_ps_ops_lowercase[] = {
	"sa",
	"sb",
	"ss",
	"pa",
	"pb",
	"ra",
	"rb",
	"rr",
	"rra",
	"rrb",
	"rrr",
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

void	output_ps_ops(const t_vector *ops)
{
	size_t	i;

	i = 0;
	while (i < ops->size)
	{
		ft_printf("%s\n", g_ps_ops_lowercase[ops->data[i]]);
		i++;
	}
}

static const char * const delimiters[] = {
"+=======+",
"+=a strt+",
"+=a end=+",
"+=======+",
"=======+\n",
"=b strt+\n",
"=b end=+\n",
"=======+\n",
};

void	print_sub_stacks(const t_sub_stack *a, const t_sub_stack *b)
{
	size_t	i;

	i = 0;
	while (i < a->stack->size || i < b->stack->size)
	{
		ft_printf(delimiters[(i == sub_stack_start(a))
			+ ((i == sub_stack_end(a)) << 1)]);
		ft_printf(delimiters[(i == sub_stack_start(b))
			+ ((i == sub_stack_end(b)) << 1) + 4]);
		if (i < a->stack->size)
			ft_printf("| %5d ", a->stack->data[i]);
		else
			ft_printf("|       ");
		if (i < b->stack->size)
			ft_printf("| %5d |\n", b->stack->data[i]);
		else
			ft_printf("|       |\n");
		i++;
	}
	ft_printf("+===A===+===B===+\n");
}
