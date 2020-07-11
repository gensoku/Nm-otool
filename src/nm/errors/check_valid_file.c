/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 05:30:17 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/03 05:30:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			check_valid_file(void *data, size_t off)
{
	if (data + off < get_nm_env(NULL)->addr + get_nm_env(NULL)->size)
		return (0);
	return (1);
}
