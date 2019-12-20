/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:06 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/26 13:14:08 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		spec_cc(t_prnf *prnf_param)
{
	char			ch[prnf_param->width + 5];
	int				temp;
	unsigned int	input;
	int				len;

	prnf_param->curr++;
	if (prnf_param->width > 1)
	{
		temp = (!(prnf_param->flags & 1) && prnf_param->flags & 2) ? '0' : ' ';
		ft_memset(ch, temp, prnf_param->width + 5);
		temp = (prnf_param->flags & 1) ? 0 : prnf_param->width - 1;
	}
	else
		temp = 0;
	input = (unsigned int)va_arg(prnf_param->ap, unsigned int);
	len = ft_wcharlen(input);
	decode_utf(&ch[temp], input, len);
	temp = (prnf_param->width > 1) ? prnf_param->width + len : len;
	write(1, ch, temp);
	prnf_param->n += temp;
	return (0);
}

int		spec_c(t_prnf *prnf_param)
{
	char	ch[prnf_param->width + 1];
	int		temp;

	if (prnf_param->size == 4)
		return (spec_cc(prnf_param));
	prnf_param->curr++;
	if (prnf_param->width > 1)
	{
		temp = (!(prnf_param->flags & 1) && prnf_param->flags & 2) ? '0' : ' ';
		ft_memset(ch, temp, prnf_param->width);
		temp = (prnf_param->flags & 1) ? 0 : prnf_param->width - 1;
		ch[temp] = (char)va_arg(prnf_param->ap, int);
	}
	else
		ch[0] = (char)va_arg(prnf_param->ap, int);
	temp = (prnf_param->width > 1) ? prnf_param->width : 1;
	write(1, ch, temp);
	prnf_param->n += temp;
	return (0);
}
