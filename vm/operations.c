/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:28:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/11/28 19:11:34 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	decorator(t_car *car)
{
	ft_printf(" ---%s--- ", car->oper.name);
	car->oper = (t_oper){"", NULL, 0};
}

void	moke_up_function(t_car *car)
{
	decorator(car);
}

/*
** If operation is invalid, move carry to the next byte
** and put it to the next unit at timeline
*/

void	invalid_operation(t_car *car)
{
	car->pos = (car->pos + 1) % MEM_SIZE;
	decorator(car);
}

t_oper	get_operation(char code)
{

	static t_oper	operations[] = {
			{"live", ft_live, 10, FALSE, 4},
			{"ld", ft_ld, 5, TRUE, 4},
			{"st", ft_st, 5, TRUE, 4},
			{"add", ft_add, 10, TRUE, 4},
			{"sub", ft_sub, 10, TRUE, 4},
			{"and", ft_and, 6, TRUE, 4},
			{"or", ft_or, 6, TRUE, 4},
			{"xor", ft_xor, 6, TRUE, 4},
			{"zjmp", ft_zjmp, 20, FALSE, 2},
			{"ldi", ft_ldi, 25, TRUE, 2},
			{"sti", ft_sti, 25, TRUE, 2},
			{"fork", ft_fork, 800, FALSE, 2},
			{"lld", ft_lld, 10, TRUE, 4},
			{"lldi", ft_lldi, 50, TRUE, 2},
			{"lfork", ft_lfork, 1000, FALSE, 2},
			{"aff", ft_aff, 2, TRUE, 4},
			{"inval", moke_up_function, 1, FALSE, 4}
	};
	ft_printf(" ---set operation--- ");
	return (code > 0 && code <= NUMBER_OF_OPERATIONS ?
	operations[code - 1] : operations[NUMBER_OF_OPERATIONS]);
}

