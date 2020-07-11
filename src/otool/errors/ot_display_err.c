/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_display_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:55:52 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 03:55:53 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int			ot_display_err_fd(char *content, char *err_type, int fd)
{
	content ? ft_putstr_fd(content, fd) : NULL;
	content ? ft_putstr_fd(": ", fd) : NULL;
	ft_putendl_fd(err_type, fd);
	return (EXIT_FAILURE);
}

int			ot_display_err_ret(char *content, char *err_type, int ret)
{
	content ? ft_putstr_fd(content, 2) : NULL;
	content ? ft_putstr_fd(": ", 2) : NULL;
	ft_putendl_fd(err_type, 2);
	return (ret);
}

int			ot_display_err(char *content, char *err_type)
{
	content ? ft_putstr_fd(content, 2) : NULL;
	content ? ft_putstr_fd(": ", 2) : NULL;
	ft_putendl_fd(err_type, 2);
	return (EXIT_FAILURE);
}
