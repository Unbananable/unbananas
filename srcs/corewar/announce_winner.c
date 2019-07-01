/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:57:49 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/01 11:29:11 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	announce_winner_visu(t_cor *cor, int winner_no, int i)
{
	werase(cor->visu->arena_period_bar);
	wmove(cor->visu->arena_period_bar, 2, 20);
	wprintw(cor->visu->arena_period_bar,
			"Contestant %d, \"%s\", has won ! Congratulations !!\n",
			winner_no, cor->champs[i]->head.prog_name);
	wattron(cor->visu->arena_period_bar, COLOR_PAIR(GRAY_CURSOR));
	box(cor->visu->arena_period_bar, '*', '*');
	wattroff(cor->visu->arena_period_bar, COLOR_PAIR(GRAY_CURSOR));
	wrefresh(cor->visu->arena_period_bar);
}

void		announce_winner(t_cor *cor)
{
	int		winner_no;
	int		i;

	winner_no = cor->last_alive;
	i = -1;
	while (cor->champs[++i])
		if (cor->champs[i]->player_no == winner_no)
		{
			if (cor->visual_on)
			{
				announce_winner_visu(cor, winner_no, i);
				return ;
			}
			ft_printf("Contestant %d, \"%s\", has won !\n", winner_no,
					cor->champs[i]->head.prog_name);
			return ;
		}
	ft_printf("No winner...\n");
}
