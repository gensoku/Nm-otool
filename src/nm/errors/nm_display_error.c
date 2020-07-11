/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_display_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 07:59:59 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/26 08:00:00 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			nm_display_err(char *content, char *err_type)
{
	content ? ft_putstr_fd(content, 2) : NULL;
	content ? ft_putstr_fd(": ", 2) : NULL;
	ft_putendl_fd(err_type, 2);
	return (EXIT_FAILURE);
}
