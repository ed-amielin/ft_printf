/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamielin <eamielin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:33:50 by eamielin          #+#    #+#             */
/*   Updated: 2019/02/28 16:33:51 by eamielin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define RETRYMALLOC 10

typedef struct		s_prnf
{
	va_list			ap;
	char			*curr;
	size_t			n;
	char			flags;
	int				width;
	int				precis;
	int				size;
	int				capital;
	char			specs[18];
	int				(*run[18])(struct s_prnf *);
}					t_prnf;

int					ft_printf(char *orig, ...);
int					init_specs(t_prnf *prnf_param);
int					init_run(t_prnf *prnf_param);
int					is_long(char c);
int					is_flag(char c);
void				*ed_memalloc(size_t size);
int					flags(t_prnf *prnf_param, char *current);
int					width(t_prnf *prnf_param, char *current);
int					precis(t_prnf *prnf_param, char *current);
int					size(t_prnf *prnf_param, char *current);
int					specifier(t_prnf *prnf_param, char *current);
int					spec_cc(t_prnf *prnf_param);
int					spec_c(t_prnf *prnf_param);
int					spec_ss(t_prnf *prnf_param);
int					spec_s(t_prnf *prnf_param);
int					spec_d(t_prnf *prnf_param);
int					spec_dd(t_prnf *prnf_param);
int					spec_i(t_prnf *prnf_param);
int					spec_o(t_prnf *prnf_param);
int					spec_oo(t_prnf *prnf_param);
int					spec_u(t_prnf *prnf_param);
int					spec_uu(t_prnf *prnf_param);
int					spec_x(t_prnf *prnf_param);
int					spec_xx(t_prnf *prnf_param);
int					spec_p(t_prnf *prnf_param);
int					spec_f(t_prnf *prnf_param);
int					spec_a(t_prnf *prnf_param);
int					work_d(char *str, int strlen, char plus,
															t_prnf *prnf_param);
int					un_spec(t_prnf *prnf_param);
char				*next_d(t_prnf *prnf_param, char *str, int wlenth,
																	char plus);
int					work_x(char *str, int strlen, char plus,
															t_prnf *prnf_param);
char				*next_x(t_prnf *prnf_param, char *str, int wlenth,
																	char plus);
int					write_ls(t_prnf *prnf_param, wchar_t *str, int strlen,
																	int width);
int					ft_wstrbytes(wchar_t *str, int precis);
int					write_s(t_prnf *prnf_param, char *str, int strlen);
long double			rounding(long double number, int precis);
char				*ft_ftoa(long double number, int precis);
char				*ftoa1(char *str, long double number, int count,
														long double *processed);
char				*ftoa2(char *str, long double number, int precis,
														long double processed);
long long			get_nbr(t_prnf *prnf_param);
unsigned long long	get_unsigned_nbr(t_prnf *prnf_param);
int					swap_char(char *first, char *second);
int					ft_wcharlen(int input);
void				decode_utf(char *ch, int input, int len);
int					text(t_prnf *prnf_param, char *current);

#endif
