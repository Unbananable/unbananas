/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaiel <anaiel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 17:51:11 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/13 09:54:11 by anaiel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 and arg2 are the VALUES extracted from the 1st and 2nd args
*/

static void	execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	long	tmp;

	if (cor->arena[restricted_addr(proc->idx + proc->move + 1)]
			&& cor->arena[restricted_addr(proc->idx + proc->move + 1)]
			<= REG_NUMBER)
	{
		tmp = (int)arg1 + (int)arg2;
		tmp = (tmp < INT_MIN) ? INT_MIN : tmp;
		tmp = (tmp > INT_MAX) ? INT_MAX : tmp;
		proc->carry = (!tmp);
		regcpy(proc->regs[cor->arena[restricted_addr(proc->idx
					+ proc->move + 1)] - 1], (void *)&tmp);
	}
}

static int	first_arg(t_cor *cor, t_proc *proc, t_bool *to_exec, int type)
{
	int		arg1;

	arg1 = 0;
	if (type == REG_CODE)
	{
		if ((arg1 = cor->arena[restricted_addr(proc->idx + proc->move + 1)
					% MEM_SIZE]) > REG_NUMBER || !arg1)
			*to_exec = false;
		else
			arg1 = get_reg_value(proc->regs[arg1 - 1]);
		proc->move += byte_offset(type);
	}
	else
		proc->move += D2_BYTES;
	if (type == IND_CODE)
		arg1 = get_int_arg_value(cor, (proc->idx
					+ get_int_arg_value(cor, (proc->idx + proc->move + 1)
						% MEM_SIZE, IND_BYTES)) % MEM_SIZE, REG_SIZE);
	else if (type == DIR_CODE)
		arg1 = get_short_arg_value(cor, (proc->idx + proc->move + 1)
				% MEM_SIZE);
	return (arg1);
}

static int	second_arg(t_cor *cor, t_proc *proc, t_bool *to_exec, int type)
{
	int		arg2;

	arg2 = 0;
	if (type == REG_CODE)
	{
		if ((arg2 = cor->arena[restricted_addr(proc->idx + proc->move + 1)])
				> REG_NUMBER || !arg2)
			*to_exec = false;
		else
			arg2 = get_reg_value(proc->regs[arg2 - 1]);
		proc->move += byte_offset(type);
	}
	else if (type == DIR_CODE)
	{
		arg2 = get_short_arg_value(cor, (proc->idx + proc->move + 1)
				% MEM_SIZE);
		proc->move += D2_BYTES;
	}
	return (arg2);
}

/*
** LONG INDIRECT LOAD
** - opcode: 0x0E
** - wait: 50
** - argcode: yes
** - args: REG/IND/DIR(2) IND/DIR(2) REG
** - addressing retriction: no
** - carry: 1 if the sum of the arguments is 0, 1 otherwise
** - description: Stores the result of the sum of the first two arguments in
**   the register indicated by the third argument.
*/

void		instr_lldi(t_cor *cor, t_proc *proc)
{
	int		type;
	t_bool	to_exec;
	int		arg1;
	int		arg2;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == IND_CODE
				|| type == DIR_CODE));
	arg1 = first_arg(cor, proc, &to_exec, type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && (type == REG_CODE || type == DIR_CODE));
	arg2 = second_arg(cor, proc, &to_exec, type);
	type = bits_peer_type(cor, proc, THIRD_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += byte_offset(type) + OPC_BYTE;
}
