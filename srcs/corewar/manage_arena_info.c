/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arena_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 10:06:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/20 11:49:47 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void draw_constants_arena_info(t_cor *cor, int y)
{
    y += 3;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "CYCLE_TO_DIE : %d", cor->cycle_to_die);
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "CYCLE_DELTA : %d", CYCLE_DELTA);
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "NBR_LIVE : %d", NBR_LIVE);
    y += 2;
    wmove(cor->visu->arena_info, y, 3);
    wprintw(cor->visu->arena_info, "MAX_CHECKS : %d", MAX_CHECKS);
}

static void draw_cycle_proc_arena_info(t_cor *cor, int *y)
{
    wmove(cor->visu->arena_info, *y, 3);
    if (cor->visu->is_running)
        wprintw(cor->visu->arena_info, "** RUNNING **");
    else
        wprintw(cor->visu->arena_info, "** PAUSED **");
    *y += 2;
    wmove(cor->visu->arena_info, *y, 3);
    wprintw(cor->visu->arena_info, "[WIP] Cycles per second limitation : NUMBER");
    *y += 2;
    wmove(cor->visu->arena_info, *y, 3);
    wprintw(cor->visu->arena_info, "Cycle : %d", cor->curr_cycle);
    *y += 2;
    wmove(cor->visu->arena_info, *y, 3);
    wprintw(cor->visu->arena_info, "Processes : %d", cor->nb_procs);
}

static int get_champ_color(int i)
{
    if (!i)
        return (COLOR_PAIR(RED) | A_BOLD);
    if (i == 1)
        return (COLOR_PAIR(GREEN) | A_BOLD);
    if (i == 2)
        return (COLOR_PAIR(YELLOW) | A_BOLD);
    if (i == 3)
        return (COLOR_PAIR(BLUE) | A_BOLD);
    return (COLOR_PAIR(MAGENTA) | A_BOLD);
}

void manage_arena_info(t_cor *cor)
{
    int i;
    int y;
    int attribute;

    y = 2;
    werase(cor->visu->arena_info);
    draw_cycle_proc_arena_info(cor, &y);
    i = -1;
    while (++i < cor->nb_champs)
    {
        y += 3;
        wmove(cor->visu->arena_info, y, 3);
        wprintw(cor->visu->arena_info, "Player -%d : ", cor->champs[i]->player_no);
        attribute = get_champ_color(i);
        wattron(cor->visu->arena_info, attribute);
        wprintw(cor->visu->arena_info, "%s", cor->champs[i]->head.prog_name);
        wattroff(cor->visu->arena_info, attribute);
        y += 1;
        wmove(cor->visu->arena_info, y, 5);
        wprintw(cor->visu->arena_info, "Last live :                %d", cor->champs[i]->last_live);
        y += 1;
        wmove(cor->visu->arena_info, y, 5);
        wprintw(cor->visu->arena_info, "Lives in current period :  %d", cor->champs[i]->lives_in_curr_period);
    }
    draw_constants_arena_info(cor, y);
}