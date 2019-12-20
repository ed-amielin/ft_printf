/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:33:50 by eamielin          #+#    #+#             */
/*   Updated: 2019/02/28 16:33:51 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		specif_start(t_prnf *prnf_param)
{
	prnf_param->flags = 0;
	prnf_param->width = 0;
	prnf_param->precis = -1;
	prnf_param->size = 0;
	prnf_param->capital = 0;
	prnf_param->curr++;
	return (flags(prnf_param, prnf_param->curr));
}

int		work(t_prnf *prnf_param, char *current)
{
	while (*current)
	{
		prnf_param->curr = current;
		while (*current && *current != '%')
			current++;
		if (current - prnf_param->curr)
			text(prnf_param, current);
		if (*current == '%')
		{
			if (specif_start(prnf_param))
				return (-1);
		}
		current = prnf_param->curr;
	}
	return (0);
}

int		ft_printf(char *orig, ...)
{
	t_prnf		*prnf_param;
	long		result;

	if ((prnf_param = (t_prnf *)ed_memalloc(sizeof(t_prnf))) == NULL)
		return (-1);
	ft_bzero(prnf_param, sizeof(t_prnf));
	va_start(prnf_param->ap, orig);
	init_run(prnf_param);
	result = work(prnf_param, orig) ? -1 : (long)prnf_param->n;
	va_end(prnf_param->ap);
	free(prnf_param);
	return (result);
}
