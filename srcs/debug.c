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

static const char			*g_stack_ops[] = {
	"ROTATE_UP",
	"ROTATE_DOWN",
	"PUSH",
	"SWAP",
	"STOP_COMMIT",
};

static const char			*g_ps_ops[] = {
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

static const char			*g_ps_ops_lowercase[] = {
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

static const char *const	g_delimiters[] = {
	"=======+",
	"=a strt+",
	"=a end=+",
	"=======+",
	"=======+",
	"=b strt+",
	"=b end=+",
	"=======+",
};

static const char *const	g_footer[] = {
	"+===B===+===A===+\n",
	"+===B===+===A===+\n",
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

static void	check_sub_stacks(const t_sub_stack *a, const t_sub_stack *b)
{
	size_t	i;
	size_t	j;

	if (a->size == 0 || b->size == 0)
		return ;
	i = sub_stack_start(a);
	while (1)
	{
		j = sub_stack_start(b);
		while (1)
		{
			if ((a->stack->data[i] < b->stack->data[j]) ^ !a->is_a)
				ft_printf("%d %c %d\n", a->stack->data[i], "<>"[a->is_a],
					b->stack->data[j]);
			j = (j + 1) % b->stack->size;
			if (j == sub_stack_end(b))
				break ;
		}
		i = (i + 1) % a->stack->size;
		if (i == sub_stack_end(a))
			break ;
	}
}

void	print_sub_stacks(const t_sub_stack *a, const t_sub_stack *b)
{
	size_t	i;

	i = 0;
	while (i < a->stack->size || i < b->stack->size)
	{
		ft_printf("+");
		ft_printf(g_delimiters[(i == sub_stack_start(a))
			+ ((i == sub_stack_end(a)) << 1) + (!a->is_a << 2)]);
		ft_printf(g_delimiters[(i == sub_stack_start(b))
			+ ((i == sub_stack_end(b)) << 1) + (!b->is_a << 2)]);
		ft_printf("\n");
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
	ft_printf(g_footer[a->is_a]);
	check_sub_stacks(a, b);
}
