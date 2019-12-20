/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:28:45 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/26 14:28:46 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		specifier(t_prnf *prnf_param, char *current)
{
	int		i;

	prnf_param->curr = current;
	i = 0;
	while (prnf_param->specs[i])
	{
		if (prnf_param->specs[i] == *current)
			return (prnf_param->run[i](prnf_param));
		i++;
	}
	if (*current)
		return (un_spec(prnf_param));
	else
		return (0);
}

int		size(t_prnf *prnf_param, char *current)
{
	prnf_param->curr = current;
	if (current[0] == 'h' && current[1] == 'h' && (current += 2))
		prnf_param->size = (prnf_param->size > 1) ? prnf_param->size : 1;
	else if (current[0] == 'h' && current++)
		prnf_param->size = (prnf_param->size > 2) ? prnf_param->size : 2;
	else if (current[0] == 'l' && current[1] == 'l' && (current += 2))
		prnf_param->size = 3;
	else if (current[0] == 'l' && current++)
		prnf_param->size = (prnf_param->size == 3) ? prnf_param->size : 4;
	else if (current[0] == 'L' && current++)
		prnf_param->size = 5;
	else if (current[0] == 'z' && current++)
		prnf_param->size = 6;
	else if (current[0] == 'j' && current++)
		prnf_param->size = 7;
	if (is_flag(*current))
		return (flags(prnf_param, current));
	else if (*current == '.')
		return (precis(prnf_param, current));
	else if (is_long(*current))
		return (size(prnf_param, current));
	else
		return (specifier(prnf_param, current));
}

int		precis(t_prnf *prnf_param, char *current)
{
	prnf_param->curr = ++current;
	prnf_param->precis = ft_atoi(current);
	while (ft_isdigit(*current))
		current++;
	if (is_flag(*current))
		return (flags(prnf_param, current));
	else if (*current == '.')
		return (precis(prnf_param, current));
	else if (is_long(*current))
		return (size(prnf_param, current));
	else
		return (specifier(prnf_param, current));
}

int		width(t_prnf *prnf_param, char *current)
{
	prnf_param->curr = current;
	prnf_param->width = ft_atoi(current);
	while (ft_isdigit(*current))
		current++;
	if (is_flag(*current))
		return (flags(prnf_param, current));
	else if (*current == '.')
		return (precis(prnf_param, current));
	else if (is_long(*current))
		return (size(prnf_param, current));
	else
		return (specifier(prnf_param, current));
}

int		flags(t_prnf *prnf_param, char *current)
{
	while (*current)
	{
		if (*current == '-')
			prnf_param->flags = (prnf_param->flags | 1);
		else if (*current == '0')
			prnf_param->flags = (prnf_param->flags | 2);
		else if (*current == '+')
			prnf_param->flags = (prnf_param->flags | 4);
		else if (*current == ' ')
			prnf_param->flags = (prnf_param->flags | 8);
		else if (*current == '#')
			prnf_param->flags = (prnf_param->flags | 16);
		else if (ft_isdigit(*current))
			return (width(prnf_param, current));
		else if (*current == '.')
			return (precis(prnf_param, current));
		else if (is_long(*current))
			return (size(prnf_param, current));
		else
			return (specifier(prnf_param, current));
		current++;
	}
	prnf_param->curr = current;
	return (0);
}
