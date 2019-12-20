/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:49:26 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/19 19:49:27 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*next_d(t_prnf *prnf_param, char *str, int wlenth, char plus)
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
	plenth = (plus) ? strlen + 1 : strlen;
	i = (prnf_param->flags & 1) ? 0 : wlenth - plenth;
	if (plus)
		result[i++] = plus;
	ft_memcpy(&result[i], str, strlen);
	i = (plus) ? i - 1 : i;
	if (temp == '0' && (plus || str[0] == '-') && i && plus != '0')
		swap_char(&result[0], &result[i]);
	return (result);
}

int		work_d(char *str, int strlen, char plus, t_prnf *prnf_param)
{
	int		plenth;
	int		wlenth;
	char	*result;

	plenth = (plus) ? strlen + 1 : strlen;
	wlenth = (prnf_param->width > plenth) ? prnf_param->width : plenth;
	if (wlenth > strlen)
	{
		result = next_d(prnf_param, str, wlenth, plus);
		write(1, result, wlenth);
		free(result);
	}
	else
		write(1, str, strlen);
	prnf_param->n += wlenth;
	return (0);
}

int		spec_d(t_prnf *prnf_param)
{
	char		*str;
	int			strlen;
	char		plus;
	int			precis;

	prnf_param->curr++;
	precis = (prnf_param->precis == -1) ? 1 : prnf_param->precis;
	str = ft_itoa_base(get_nbr(prnf_param), 10, 1, precis);
	strlen = ft_strlen(str);
	plus = ((prnf_param->flags & 8) && str[0] != '-') ? ' ' : 0;
	plus = ((prnf_param->flags & 4) && str[0] != '-') ? '+' : plus;
	work_d(str, strlen, plus, prnf_param);
	free(str);
	return (0);
}

int		spec_dd(t_prnf *prnf_param)
{
	prnf_param->size = 4;
	return (spec_d(prnf_param));
}

int		spec_i(t_prnf *prnf_param)
{
	return (spec_d(prnf_param));
}
