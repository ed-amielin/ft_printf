/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:02:14 by eamielin          #+#    #+#             */
/*   Updated: 2019/04/19 14:02:15 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		init_specs(t_prnf *prnf_param)
{
	prnf_param->specs[0] = 'c';
	prnf_param->specs[1] = 'C';
	prnf_param->specs[2] = 's';
	prnf_param->specs[3] = 'S';
	prnf_param->specs[4] = 'p';
	prnf_param->specs[5] = 'd';
	prnf_param->specs[6] = 'D';
	prnf_param->specs[7] = 'i';
	prnf_param->specs[8] = 'o';
	prnf_param->specs[9] = 'O';
	prnf_param->specs[10] = 'u';
	prnf_param->specs[11] = 'U';
	prnf_param->specs[12] = 'x';
	prnf_param->specs[13] = 'X';
	prnf_param->specs[14] = 'f';
	prnf_param->specs[15] = 'F';
	prnf_param->specs[16] = '%';
	prnf_param->specs[17] = 0;
	return (0);
}

int		init_run(t_prnf *prnf_param)
{
	prnf_param->run[0] = &spec_c;
	prnf_param->run[1] = &spec_cc;
	prnf_param->run[2] = &spec_s;
	prnf_param->run[3] = &spec_ss;
	prnf_param->run[4] = &spec_p;
	prnf_param->run[5] = &spec_d;
	prnf_param->run[6] = &spec_dd;
	prnf_param->run[7] = &spec_i;
	prnf_param->run[8] = &spec_o;
	prnf_param->run[9] = &spec_oo;
	prnf_param->run[10] = &spec_u;
	prnf_param->run[11] = &spec_uu;
	prnf_param->run[12] = &spec_x;
	prnf_param->run[13] = &spec_xx;
	prnf_param->run[14] = &spec_f;
	prnf_param->run[15] = &spec_f;
	prnf_param->run[16] = &spec_a;
	prnf_param->run[17] = NULL;
	init_specs(prnf_param);
	return (0);
}

int		is_long(char c)
{
	if ((c == 'l') || (c == 'h') || (c == 'L') || (c == 'z') || (c == 'j'))
		return (1);
	else
		return (0);
}

int		is_flag(char c)
{
	if ((c == '-') || (c == '+') || (c == '0') || (c == ' ') || (c == '#'))
		return (1);
	else
		return (0);
}

void	*ed_memalloc(size_t size)
{
	void			*result;
	unsigned char	counter;

	counter = RETRYMALLOC;
	while (counter--)
	{
		result = malloc(size);
		if (result)
			ft_bzero(result, size);
		return (result);
	}
	ft_putstr("Exception: failed to malloc ");
	ft_putnbr(size);
	ft_putstr(" bytes for ");
	ft_putnbr(RETRYMALLOC);
	ft_putstr(" times. Break.");
	return (NULL);
}
