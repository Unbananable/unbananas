/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:09:22 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/01 19:09:04 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** First case: T_REG case
** Second case: T_IND case
*/

void		instr_st(t_cor *cor, t_proc *proc)
{
	int		i;
	int		addr;

	i = -1;
	if (cor->arena[proc.idx + BYTE1] & 0b00100000)
	{
		while (++i < REG_SIZE)
			proc.regs[cor->arena[cyd_val(proc.idx + BYTES3)]
				- 1][i] = proc.regs[cor->arena[cyd_val(proc.idx + BYTES2)] - 1][i];
		proc.idx = cyd_val(proc.idx + BYTES4);
	}
	else
	{
		cor->hex[0] = cor->arena[cyd_val(proc.idx + BYTES3)];
		cor->hex[1] = cor->arena[cyd_val(proc.idx + BYTES4)];
		addr = restricted_addr(cor, proc, ft_atos_base(cor->hex, 16));
		ft_bzero(cor->hex, REG_SIZE);
		while (++i < REG_SIZE)
			cor->arena[cyd_val(addr
					+ i)] = proc.regs[cor->arena[cyd_val(proc.idx + BYTES2)]][i];
		proc.idx = cyd_val(proc.idx + BYTES5);
	}
}
