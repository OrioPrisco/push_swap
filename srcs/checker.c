/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orio <47635210+OrioPrisco@users.noreply.g  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:15:07 by OrioPrisco        #+#    #+#             */
/*   Updated: 2023/04/03 19:57:24 by OrioPrisco       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "push_swap.h"
#include "stack.h"
#include "get_next_line.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
#include "ft_printf.h"

t_ps_ops	str_to_op(const char *str)
{
	if (!ft_strcmp(str, "sa\n"))
		return (SA);
	if (!ft_strcmp(str, "sb\n"))
		return (SB);
	if (!ft_strcmp(str, "ss\n"))
		return (SS);
	if (!ft_strcmp(str, "pa\n"))
		return (PA);
	if (!ft_strcmp(str, "pb\n"))
		return (PB);
	if (!ft_strcmp(str, "ra\n"))
		return (RA);
	if (!ft_strcmp(str, "rb\n"))
		return (RB);
	if (!ft_strcmp(str, "rr\n"))
		return (RR);
	if (!ft_strcmp(str, "rra\n"))
		return (RRA);
	if (!ft_strcmp(str, "rrb\n"))
		return (RRB);
	if (!ft_strcmp(str, "rrr\n"))
		return (RRR);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	t_env		env;
	char		*command;
	t_ps_ops	op;

	if (argc == 1)
		return (0);
	if (init_env(argc - 1, argv + 1, &env))
		return (write(2, "Error\n", 6), 1);
	command = get_next_line(0);
	while (command)
	{
		op = str_to_op(command);
		if (op == ERROR)
			return (write(2, "Error\n", 6), destroy_env(&env), free(command), 1);
		if (execute_one_checked(&env.a, &env.b, op))
			return (write(2, "Error\n", 6), destroy_env(&env), free(command), 1);
		free(command);
		command = get_next_line(0);
	}
	if (env.b.size != 0 || !vector_is_sorted(&env.a, true))
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	destroy_env(&env);
}
