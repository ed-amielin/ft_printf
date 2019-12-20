/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:54:37 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/19 19:54:40 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_s(t_prnf *prnf_param, char *str, int strlen)
{
	char	chr[prnf_param->width];
	int		temp;

	temp = (prnf_param->flags & 2) ? '0' : ' ';
	if (prnf_param->flags & 1)
		ft_memset(&chr[strlen], ' ', prnf_param->width - strlen);
	else
		ft_memset(chr, temp, prnf_param->width - strlen);
	if (prnf_param->flags & 1)
		ft_memcpy(chr, str, strlen);
	else
		ft_memcpy(&chr[prnf_param->width - strlen], str, strlen);
	write(1, chr, prnf_param->width);
	return (0);
}

int		ft_wstrbytes(wchar_t *str, int precis)
{
	int		i;
	int		temp;

	i = 0;
	if (str)
	{
		if (precis >= 0)
		{
			while (*str && precis > 0)
			{
				temp = ft_wcharlen(*str);
				if ((precis -= temp) >= 0)
					i += temp;
				str++;
			}
		}
		else
		{
			while (*str)
				i += ft_wcharlen(*str++);
		}
	}
	return (i);
}

int		write_ls(t_prnf *prnf_param, wchar_t *str, int strlen, int width)
{
	char	chr[width];
	int		temp;
	int		len;

	if (width > strlen)
	{
		temp = (prnf_param->flags & 2) ? '0' : ' ';
		if (prnf_param->flags & 1)
			ft_memset(&chr[strlen], ' ', width - strlen);
		else
			ft_memset(chr, temp, width - strlen);
	}
	temp = (prnf_param->flags & 1) ? 0 : width - strlen;
	while (*str && temp < width)
	{
		len = ft_wcharlen(*str);
		decode_utf(&chr[temp], *str, len);
		str++;
		temp += len;
	}
	write(1, chr, width);
	return (0);
}

int		spec_ss(t_prnf *prnf_param)
{
	int		strlen;
	int		width;
	wchar_t	*str;

	prnf_param->curr++;
	str = va_arg(prnf_param->ap, wchar_t *);
	strlen = ft_wstrbytes(str, prnf_param->precis);
	if (str == NULL && prnf_param->precis >= -1)
	{
		str = L"(null)";
		strlen = 6;
		if (prnf_param->precis != -1)
			strlen = (prnf_param->precis > 6) ? 6 : prnf_param->precis;
	}
	width = (prnf_param->width > strlen) ? prnf_param->width : strlen;
	write_ls(prnf_param, str, strlen, width);
	prnf_param->n += width;
	return (0);
}

int		spec_s(t_prnf *prnf_param)
{
	int		strlen;
	char	*str;

	if (prnf_param->size == 4)
		return (spec_ss(prnf_param));
	prnf_param->curr++;
	str = va_arg(prnf_param->ap, char *);
	strlen = ft_strlen(str);
	if (prnf_param->precis >= 0 && str)
		strlen = (strlen < prnf_param->precis) ? strlen : prnf_param->precis;
	if (str == NULL && prnf_param->precis >= -1)
	{
		str = "(null)";
		strlen = 6;
		if (prnf_param->precis != -1)
			strlen = (prnf_param->precis > 6) ? 6 : prnf_param->precis;
	}
	if (prnf_param->width > strlen)
		write_s(prnf_param, str, strlen);
	else
		write(1, str, strlen);
	prnf_param->n += (prnf_param->width > strlen) ? prnf_param->width : strlen;
	return (0);
}
