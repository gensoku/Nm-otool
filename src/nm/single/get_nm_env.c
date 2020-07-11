/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nm_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 07:03:14 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/26 07:03:15 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_nm_env		*get_nm_env(t_nm_env *env)
{
	static t_nm_env cur_env;

	if (env)
		cur_env = *env;
	return (&cur_env);
}
