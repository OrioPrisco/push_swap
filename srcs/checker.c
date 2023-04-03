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
	if (!ft_strcmp(str, "SA\n"))
		return (SA);
	if (!ft_strcmp(str, "SB\n"))
		return (SB);
	if (!ft_strcmp(str, "SS\n"))
		return (SS);
	if (!ft_strcmp(str, "PA\n"))
		return (PA);
	if (!ft_strcmp(str, "PB\n"))
		return (PB);
	if (!ft_strcmp(str, "RA\n"))
		return (RA);
	if (!ft_strcmp(str, "RB\n"))
		return (RB);
	if (!ft_strcmp(str, "RR\n"))
		return (RR);
	if (!ft_strcmp(str, "RRA\n"))
		return (RRA);
	if (!ft_strcmp(str, "RRB\n"))
		return (RRB);
	if (!ft_strcmp(str, "RRR\n"))
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
	command = get_next_line(1);
	while (command)
	{
		op = str_to_op(command);
		if (op == ERROR)
			return (write(2, "Error\n", 6), destroy_env(&env), 1);
		if (execute_one_checked(&env.a, &env.b, op))
			return (write(2, "Error\n", 6), destroy_env(&env), 1);
		free(command);
		command = get_next_line(1);
	}
	if (env.b.size != 0 || !vector_is_sorted(&env.a, true))
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	destroy_env(&env);
}
