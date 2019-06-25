/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:00:05 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/25 14:57:54 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		dump(t_cor *cor)
{
	int		i;
	int		j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%#.4x : ", i); // [TO DO] Quand on utilise # a la place de '0x', ft_printf a un heap buffer overflow
		j = -1;
		while (++j < 32)
			ft_printf("%.2x ", cor->arena[i + j]);
		ft_putchar('\n');
		i += j;
	}
	end(cor);
}
