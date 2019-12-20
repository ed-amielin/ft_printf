/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_ap_unspec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:21:12 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/26 14:21:13 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		un_spec(t_prnf *prnf_param)
{
	char	ch[prnf_param->width + 1];
	int		temp;

	if (prnf_param->width > 1)
	{
		temp = (!(prnf_param->flags & 1) && prnf_param->flags & 2) ? '0' : ' ';
		ft_memset(ch, temp, prnf_param->width);
		temp = (prnf_param->flags & 1) ? 0 : prnf_param->width - 1;
		ch[temp] = prnf_param->curr[0];
	}
	else
		ch[0] = prnf_param->curr[0];
	temp = (prnf_param->width > 1) ? prnf_param->width : 1;
	write(1, ch, temp);
	prnf_param->n += temp;
	prnf_param->curr++;
	return (0);
}

int		spec_p(t_prnf *prnf_param)
{
	void		*ptr;
	char		*str;
	int			strlen;
	int			precis;

	prnf_param->curr++;
	ptr = (void *)va_arg(prnf_param->ap, void *);
	precis = (prnf_param->precis == -1) ? 1 : prnf_param->precis;
	if ((str = ft_itoa_base((long long)ptr, 16, 0, precis)) == NULL)
		return (-1);
	strlen = ft_strlen(str);
	work_x(str, strlen, 1, prnf_param);
	free(str);
	return (0);
}

int		spec_a(t_prnf *prnf_param)
{
	char	ch[prnf_param->width + 1];
	int		temp;

	prnf_param->curr++;
	if (prnf_param->width > 1)
	{
		temp = (!(prnf_param->flags & 1) && prnf_param->flags & 2) ? '0' : ' ';
		ft_memset(ch, temp, prnf_param->width);
		temp = (prnf_param->flags & 1) ? 0 : prnf_param->width - 1;
		ch[temp] = '%';
	}
	else
		ch[0] = '%';
	temp = (prnf_param->width > 1) ? prnf_param->width : 1;
	write(1, ch, temp);
	prnf_param->n += temp;
	return (0);
}
