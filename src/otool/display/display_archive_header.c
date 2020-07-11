/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_archive_header.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 04:31:30 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/10 04:31:31 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void				display_header(struct ar_hdr *header)
{
	int				n;

	n = 0;
	if ((void *)get_ot_env(NULL)->file + ft_atoi(header->ar_size)
		> (void *)get_ot_env(NULL)->file + get_ot_env(NULL)->size)
		return ;
	ft_putchar('0');
	put_nstr_delim((char *)header->ar_mode, 8, ' ');
	ft_putstr(" ");
	n = ft_nlen_char((char *)header->ar_uid, 3, ' ');
	ft_loop_char(n, ' ');
	put_nstr_delim((char *)header->ar_uid, 6, ' ');
	ft_putchar('/');
	n = ft_nlen_char((char *)header->ar_gid, 3, ' ');
	put_nstr_delim((char *)header->ar_gid, 6, ' ');
	n ? ft_loop_char(n, ' ') : 0;
	ft_putstr(" ");
	n = ft_nlen_char((char *)header->ar_size, 5, ' ');
	ft_loop_char(n, ' ');
	put_nstr_delim((char *)header->ar_size, 10, ' ');
	ft_putchar(' ');
	put_nstr_delim((char *)header->ar_date, 12, ' ');
	ft_putchar(' ');
	put_nstr_delim((char *)header->ar_name, 16, ' ');
	ft_putchar('\n');
}
