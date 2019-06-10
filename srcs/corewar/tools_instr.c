/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:28:41 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/10 13:35:14 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short	get_short_arg_value(t_cor *cor, int idx)
{
	return ((short)(cor->arena[idx % MEM_SIZE] * 256 + cor->arena[(idx + 1) % MEM_SIZE]));
}

int		get_int_arg_value(t_cor *cor, int idx, int size)
{
	int		res;
	int		i;

	res = cor->arena[idx % MEM_SIZE];
	i = 0;
	while (++i < size)
		res = res * 256 + cor->arena[(idx + i) % MEM_SIZE];
	return (res);
}