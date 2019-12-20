/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:23:35 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/26 14:23:36 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			get_nbr(t_prnf *prnf_param)
{
	if (prnf_param->size == 0)
		return ((int)va_arg(prnf_param->ap, int));
	else if (prnf_param->size == 1)
		return ((char)va_arg(prnf_param->ap, int));
	else if (prnf_param->size == 2)
		return ((short)va_arg(prnf_param->ap, int));
	else if (prnf_param->size == 3)
		return ((long long)va_arg(prnf_param->ap, long long));
	else if (prnf_param->size == 4)
		return ((long)va_arg(prnf_param->ap, long));
	else if (prnf_param->size == 6)
		return ((size_t)va_arg(prnf_param->ap, size_t));
	else if (prnf_param->size == 7)
		return ((intmax_t)va_arg(prnf_param->ap, intmax_t));
	return (0);
}

unsigned long long	get_unsigned_nbr(t_prnf *prnf_param)
{
	if (prnf_param->size == 0)
		return ((unsigned int)va_arg(prnf_param->ap, unsigned int));
	else if (prnf_param->size == 1)
		return ((unsigned char)va_arg(prnf_param->ap, unsigned int));
	else if (prnf_param->size == 2)
		return ((unsigned short)va_arg(prnf_param->ap, unsigned int));
	else if (prnf_param->size == 3)
		return ((unsigned long long)va_arg(prnf_param->ap, unsigned long long));
	else if (prnf_param->size == 4)
		return ((unsigned long)va_arg(prnf_param->ap, unsigned long));
	else if (prnf_param->size == 6)
		return ((size_t)va_arg(prnf_param->ap, size_t));
	else if (prnf_param->size == 7)
		return ((uintmax_t)va_arg(prnf_param->ap, uintmax_t));
	return (0);
}
