/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool_lib_func.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 06:40:56 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/26 06:40:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_LIB_FUNC_H
# define NM_OTOOL_LIB_FUNC_H

int						is_opt_set(unsigned long flags, char a);
unsigned long			opts_get_static(unsigned long value);
int						check_opts(const char *av, char *opts,
	unsigned long *flags, int opts_flags);
unsigned int			swap_uint32(unsigned int val);
unsigned long			swap_uint64(unsigned long val);
int						size_ulong(unsigned long val);
char					*conver_base_unsigned(char maj,
	unsigned long x, int base);
unsigned int			size_uint(unsigned int x);
void					ft_loop_char(unsigned int x, char c);
int						put_nstr_delim(char *str, int n, char delim);
int						ft_nlen_char(char *str, int n, char delim);
int						ft_power(int x, unsigned int y);

#endif
