/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_swap_utf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:26:35 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/26 14:26:36 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		text(t_prnf *prnf_param, char *current)
{
	prnf_param->n += current - prnf_param->curr;
	write(1, prnf_param->curr, current - prnf_param->curr);
	prnf_param->curr = current;
	return (0);
}

void	decode_utf(char *ch, int input, int len)
{
	if (len == 1)
		ch[0] = (char)input;
	else
	{
		if (len == 2)
			ch[0] = ((input & 1984) >> 6) | 192;
		else
		{
			if (len == 3)
				ch[0] = ((input & 61440) >> 12) | 224;
			else
			{
				ch[0] = ((input & 1835008) >> 18) | 240;
				ch[len - 3] = ((input & 258048) >> 12) | 128;
			}
			ch[len - 2] = ((input & 4032) >> 6) | 128;
		}
		ch[len - 1] = (input & 63) | 128;
	}
}

int		ft_wcharlen(int input)
{
	if (input < 128)
		return (1);
	if (input < 2048)
		return (2);
	if (input < 65536)
		return (3);
	return (4);
}

int		swap_char(char *first, char *second)
{
	char	temp;

	temp = *first;
	*first = *second;
	*second = temp;
	return (0);
}
