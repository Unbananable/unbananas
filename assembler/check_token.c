/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:04:55 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/01 17:27:19 by abossard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		error_name_comment(t_champion *c, t_token *t, t_token *next, int nb_tok)
{
	int error;

	error = 0;
	if (nb_tok == 1 || !next || next->type != STRING)
		error += error_champion(c, "STRING not found", t->line);
	else if (!next->value.data ||
		(t->type == NAME && ft_strlen(next->value.data) > PROG_NAME_LENGTH) ||
		(t->type == COMMENT && ft_strlen(next->value.data) > COMMENT_LENGTH))
	{
		ft_printf("NULL ?? <%s> <%d>\n",
				next->value.data, ft_strlen(next->value.data));
		error += error_champion(c, "name or comment doesn't have a good format",
		t->line);
	}
	else if (!ft_strlen(next->value.data))
		warning_champion(c, "String empty ", t->line);
	else if (nb_tok > 2 && !error)
		error += error_champion(c, "trop d'element sur cette ligne", t->line);
	return (error);
}

void	check_name_comment(t_champion *c, t_token *t, t_token *next, int nb_tok)
{
	if (!error_name_comment(c, t, next, nb_tok))
	{
		if ((t->type == NAME && c->hasname) ||
			(t->type == COMMENT && c->hascomment))
			c->number_warning += warning_champion(c,
			"champion has already a name or a comment", t->line);
		(t->type != NAME) ? ft_strcpy(c->header->comment, next->value.data) :
			ft_strcpy(c->header->prog_name, next->value.data);
	}
	delete_token(t);
	delete_token(next);
}

int		verify_champion_line(t_champion *c, int t, int deb, int tok_line)
{
	if (t == NAME || t == COMMENT)
		check_name_comment(c, c->tokens[deb], c->tokens[deb + 1], tok_line);
	else if (t == LABEL)
		check_label(c, c->tokens[deb], deb, tok_line);
	else if (t == INSTRUCTION)
		check_instruction(c, c->tokens[deb], deb, tok_line);
	else if (t == UNKNOWN)
		error_champion(c, "moi pas comprendre", c->tokens[deb]->line);
	else
		ft_printf("n'a rien a faire la (%d)\n", c->tokens[deb]->line);
	return (1);
}