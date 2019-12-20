/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_ou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:44:39 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/26 13:44:39 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		spec_o(t_prnf *prnf_param)
{
	char		*str;
	int			strlen;
	int			sharp;
	int			precis;

	prnf_param->curr++;
	precis = (prnf_param->precis == -1) ? 1 : prnf_param->precis;
	str = ft_itoa_base(get_unsigned_nbr(prnf_param), 8, 0, precis);
	strlen = ft_strlen(str);
	sharp = ((prnf_param->flags & 16) && str[0] != '0') ? '0' : 0;
	work_d(str, strlen, sharp, prnf_param);
	free(str);
	return (0);
}

int		spec_oo(t_prnf *prnf_param)
{
	prnf_param->size = 4;
	return (spec_o(prnf_param));
}

int		spec_u(t_prnf *prnf_param)
{
	char		*str;
	int			strlen;
	int			precis;

	prnf_param->curr++;
	precis = (prnf_param->precis == -1) ? 1 : prnf_param->precis;
	if ((str = ft_itoa_base(get_unsigned_nbr(prnf_param), 10, 0, precis))
		== NULL)
		return (-1);
	strlen = ft_strlen(str);
	work_d(str, strlen, 0, prnf_param);
	free(str);
	return (0);
}

int		spec_uu(t_prnf *prnf_param)
{
	prnf_param->size = 4;
	return (spec_u(prnf_param));
}
