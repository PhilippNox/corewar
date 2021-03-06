/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djon-con <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 14:44:06 by djon-con          #+#    #+#             */
/*   Updated: 2020/05/09 14:44:06 by djon-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	validate_permitted_types(t_arg *args)
{
	if ((args[0].type == DIR || args[0].type == IND)
		&&
		args[1].type == REG
		&&
		args[2].type == NONE
		&&
		args[3].type == NONE)
		return (1);
	return (0);
}

static void	op_unique_commands(t_car *car,
								t_cbox *cbox,
								t_arg args[CW_MAX_ARGS])
{
	int		reg;
	int		value;

	value = get_int_from_arg(car, cbox, args[0]);
	reg = args[1].value;
	car_change_player(reg, -car->regs[0], -value, cbox);
	car->regs[REG(reg)] = value;
	if (value == 0)
		car->carry = 1;
	else
		car->carry = 0;
	if (cbox->flags & V_FLAG_OPER)
		ft_printf("P % 4lu | ld %d r%d\n", car->id + 1, value, reg);
}

void		ft_ld(t_car *car, t_cbox *cbox)
{
	t_carbox carbox;

	carbox.cbox = cbox;
	carbox.car = car;
	carbox.op_command_code = LD_COMMAND_CODE;
	exec_command(&carbox, op_unique_commands, validate_permitted_types);
}
