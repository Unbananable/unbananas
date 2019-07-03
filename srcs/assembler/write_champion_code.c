/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_champion_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 23:03:42 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/03 12:24:59 by abossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

long long	ft_cast_element(long long value, unsigned char size)
{
	if (size == 1)
		value = (char)value;
	else if (size == 2)
		value = (short int)value;
	else if (size == 4)
		value = (int)value;
	else if (size == 8)
		value = (long)value;
	else if (size == 16)
		value = (long long)value;
	return (value);
}

int oo = 0;

void		write_line_token(t_token *token, int fd)
{
	int		i;
	int		id;
	char	*tmp;
	char	tab[1000];
	char	separator[3];

	i = -1;
	separator[0] = SEPARATOR_CHAR;
	separator[1] = ' ';
	separator[2] = '\0';
	ft_bzero(tab, 1000);
	ft_strcat(tab, token->value.operation->operation);
	ft_strcat(tab, "\t");
	id = token->value.operation->id;
	while (++i < token->value.operation->number_param)
	{
		if (token->param[i]->type == REGISTER)
			ft_strcat(tab, "r");
		else if (token->param[i]->type == DIRECT)
			ft_strcat(tab, "%");
		tmp = ft_itoa(ft_cast_element(token->param[i]->value.number,
				size_token(token->param[i]->type, id)));
		ft_strcat(tab, tmp);
		(i < token->value.operation->number_param - 1) ?
			ft_strcat(tab, separator) : ft_strcat(tab, "\n");
		ft_strdel(&tmp);
	}
	ft_putstr_fd(tab, fd);
}

int			write_champion_prog(t_champion *champion, char *str)
{
	int fd;
	int i;

	i = -1;
	str = ft_strnjoin(str, "9.s", ft_strlen(str) - 4);
	fd = open(str, O_WRONLY | O_CREAT);
	ft_memdel((void**)&str);
	ft_printf("name \"%s\", ize :%d,\"%s\":", champion->header->prog_name,
			champion->header->prog_size, champion->header->comment);
	ft_putstr_fd(NAME_CMD_STRING, fd);
	ft_putstr_fd(" \"", fd);
	ft_putstr_fd(champion->header->prog_name, fd);
	ft_putstr_fd("\"\n", fd);
	ft_putstr_fd(COMMENT_CMD_STRING, fd);
	ft_putstr_fd(" \"", fd);
	ft_putstr_fd(champion->header->comment, fd);
	ft_putstr_fd("\"\n", fd);
	ft_printf("ecriture\n");
	while (++i < champion->number_token)
		write_line_token(champion->tokens[i], fd);
	close(fd);
	return (0);
}