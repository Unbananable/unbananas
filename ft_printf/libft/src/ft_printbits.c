/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:10:12 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/23 14:11:07 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printbits(char c)
{
	unsigned char	bit;

	bit = 128;
	while (bit)
	{
		if (bit & c)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		bit = bit >> 1;
	}
}