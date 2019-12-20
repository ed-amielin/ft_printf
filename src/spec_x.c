/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:52:00 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/19 19:52:00 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*next_x(t_prnf *prnf_param, char *str, int wlenth, char plus)
{
	char	*result;
	int		temp;
	int		strlen;
	int		plenth;
	int		i;

	if ((result = (char *)ed_memalloc(wlenth)) == NULL)
		return (NULL);
	temp = (!(prnf_param->flags & 1) && (prnf_param->flags & 2) &&
			(prnf_param->precis == -1)) ? '0' : ' ';
	ft_memset(result, temp, wlenth);
	strlen = ft_strlen(str);
	plenth = (plus) ? strlen + 2 : strlen;
	i = (prnf_param->flags & 1) ? 0 : wlenth - plenth;
	if (plus == 1)
	{
		result[i++] = '0';
		result[i++] = 'x';
	}
	ft_memcpy(&result[i], str, strlen);
	i = (plus) ? i - 2 : i;
	if (temp == '0' && plus && i)
		swap_char(&result[1], &result[i + 1]);
	return (result);
}

int		work_x(char *str, int strlen, char plus, t_prnf *prnf_param)
{
	int		plenth;
	int		wlenth;
	char	*result;

	plenth = (plus) ? strlen + 2 : strlen;
	wlenth = (prnf_param->width > plenth) ? prnf_param->width : plenth;
	if (wlenth > strlen)
	{
		result = next_x(prnf_param, str, wlenth, plus);
		if (prnf_param->capital)
			ft_capitalizer(result);
		write(1, result, wlenth);
		free(result);
	}
	else
	{
		if (prnf_param->capital)
			ft_capitalizer(str);
		write(1, str, wlenth);
	}
	prnf_param->n += wlenth;
	return (0);
}

int		spec_x(t_prnf *prnf_param)
{
	char				*str;
	unsigned long long	nbr;
	int					strlen;
	int					sharp;
	int					precis;

	prnf_param->curr++;
	precis = (prnf_param->precis == -1) ? 1 : prnf_param->precis;
	nbr = get_unsigned_nbr(prnf_param);
	str = ft_itoa_base(nbr, 16, 0, precis);
	strlen = ft_strlen(str);
	sharp = ((prnf_param->flags & 16) && str[0] && nbr) ? 1 : 0;
	work_x(str, strlen, sharp, prnf_param);
	free(str);
	return (0);
}

int		spec_xx(t_prnf *prnf_param)
{
	prnf_param->capital = 1;
	return (spec_x(prnf_param));
}
