/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:04:29 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/03 11:44:39 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** arg1 is the int VALUE to store into arg2 (the targeted register number)
*/

static void execute_instr(t_cor *cor, t_proc *proc, int arg1, int arg2)
{
	proc->carry= (!arg1);
	ft_memcpy(proc->regs[arg2], arg1, REG_SIZE);
}

/*
** S (ID/D4) D (RG)
*/

void instr_ld(t_cor *cor, t_proc *proc)
{
	t_bool to_exec;
	int type;
	int arg1;
	int arg2;

	to_exec = true;
	proc->move = ARGC_BYTE;
	type = bits_peer_type(cor, proc, FIRST_PARAM);
	to_exec = (to_exec && (type == IND_CODE || type == DIR_CODE));
	if (type == IND_CODE)
		arg1 = get_int_arg_val(cor, proc->idx + (get_int_arg_val(cor, proc->idx + proc->move + 1, IND_BYTES) % IDX_MOD), REG_SIZE);
	else if (type == DIR_CODE)
		arg1 = get_int_arg_val(cor, proc->idx + proc->move + 1, D4_BYTES);
	proc->move += byte_offset(type);
	type = bits_peer_type(cor, proc, SECOND_PARAM);
	to_exec = (to_exec && type == REG_CODE);
	if ((arg2 = cor->arena[(proc->idx + proc->move + 1) % MEM_SIZE]) >= REG_NUMBER)
		to_exec = false;
	proc->move += byte_offset(type);
	if (to_exec)
		execute_instr(cor, proc, arg1, arg2);
	proc->move += OPC_BYTE;
}
