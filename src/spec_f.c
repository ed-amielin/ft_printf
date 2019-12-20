/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:36:28 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/26 13:36:28 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ftoa2(char *str, long double number, int precis,
														long double processed)
{
	int		i;

	number = (number < 0) ? number * -1 : number;
	number -= processed;
	i = 0;
	if (precis)
		str[i++] = '.';
	while (precis--)
	{
		number *= 10;
		str[i++] = (int)number + '0';
		number -= (int)number;
	}
	if ((i - 1) > 19 && str[i - 1] < '9')
		str[i - 1]++;
	str[i] = '\0';
	return (str);
}

char		*ftoa1(char *str, long double number, int count,
														long double *processed)
{
	long double	factor;

	if (number < 0)
		str[0] = '-';
	number = (number < 0) ? number * -1 : number;
	str[--count] = '\0';
	*processed = 0;
	if (number < 1)
		str[--count] = '0';
	else
	{
		str[--count] = (unsigned long long)number % 10 + '0';
		*processed = (unsigned long long)number % 10;
		factor = 1;
		while ((number /= 10) >= 1)
		{
			str[--count] = (unsigned long long)number % 10 + '0';
			factor *= 10;
			*processed += ((unsigned long long)number % 10) * factor;
		}
	}
	return (str);
}

char		*ft_ftoa(long double number, int precis)
{
	char		*str;
	int			count;
	long double	temp;
	long double	processed;

	count = (number < 0) ? 2 : 1;
	temp = (number < 0) ? number * -1 : number;
	if (temp < 1)
		count++;
	else
	{
		count++;
		while ((temp /= 10) >= 1)
			count++;
	}
	if ((str = (char *)ed_memalloc(count + precis + 1)) == NULL)
		return (NULL);
	ftoa1(str, number, count, &processed);
	ftoa2(&str[count - 1], number, precis, processed);
	return (str);
}

long double	rounding(long double number, int precis)
{
	long double	orig;
	long double	processed;
	long double	factor;

	orig = number;
	number = (number < 0) ? number * -1 : number;
	if (number < 1)
		processed = 0;
	else
	{
		processed = (int)number % 10;
		factor = 1;
		while (((number /= 10) >= 1) && (factor *= 10))
			processed += ((unsigned long long)number % 10) * factor;
	}
	number = (orig < 0) ? orig * -1 - processed : orig - processed;
	factor = 1;
	while (precis-- && (number *= 10))
		factor /= 10;
	if (((unsigned long long)(number * 10) % 10) > 4)
		orig = (orig < 0) ? orig - factor : orig + factor;
	return (orig);
}

int			spec_f(t_prnf *prnf_param)
{
	char		*str;
	int			strlen;
	long double	number;
	char		plus;

	prnf_param->curr++;
	if (prnf_param->size == 5)
		number = (long double)va_arg(prnf_param->ap, long double);
	else
		number = (double)va_arg(prnf_param->ap, double);
	prnf_param->precis = (prnf_param->precis == -1) ? 6 : prnf_param->precis;
	prnf_param->precis = (prnf_param->precis < 0) ? 0 : prnf_param->precis;
	number = rounding(number, prnf_param->precis);
	if ((str = ft_ftoa(number, prnf_param->precis)) == NULL)
		return (-1);
	strlen = ft_strlen(str);
	plus = ((prnf_param->flags & 8) && str[0] != '-') ? ' ' : 0;
	plus = ((prnf_param->flags & 4) && str[0] != '-') ? '+' : plus;
	prnf_param->precis = -1;
	work_d(str, strlen, plus, prnf_param);
	free(str);
	return (0);
}
