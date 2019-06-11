/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:28:36 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/10 15:00:08 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Copies each champion's redcode at the correct place in the arena, depending
** on the number of champions.
*/

static void	place_champions(t_cor *cor)
{
	int				i;
	unsigned int	j;

	i = -1;
	while (++i < cor->nb_champs)
	{
		j = 0;
		while (j < cor->champs[i]->head.prog_size)
		{
			cor->arena[i * MEM_SIZE / cor->nb_champs + j] = cor->champs[i]
				->redcode[j];
			j++;
		}
	}
}

/*
** Creates a new proc for each champion (procs are stores as a chained list) and
** adds it at the beginning of the list.
** The the proc is placed at the beginning of the champion's instruction in the
** arena. The registers are initialised to 0, except the first one which is
** initialised to -1 * player_no (the champion's player number) (/!\ the vm
** is big endian while the Mac is little endian, hence the memcpy_big.
*/

void		initialize_procs(t_cor *cor)
{
	int		i;
	t_proc	*new;
	int		*player_no;

	i = -1;
	while (++i < cor->nb_champs)
	{
		if (!(new = new_proc()))
			error(cor, "malloc failed");
		new->n = i;
		new->wait = 0;
		new->carry = false;
		new->last_live_cycle = 0;
		new->idx = i * MEM_SIZE / cor->nb_champs;
		if (!(player_no = (int *)malloc(sizeof(int))))
			error(cor, "malloc failed");
		*player_no = -1 * cor->champs[i]->player_no;
		memcpy_big(new->regs[0], player_no, sizeof(char) * REG_SIZE);
		free(player_no);
		cor->procs = add_proc(new, cor->procs);
	}
}

void		arena_setup(t_cor *cor)
{
	place_champions(cor);
	initialize_procs(cor);
}
