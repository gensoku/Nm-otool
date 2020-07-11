/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool_lib_define.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 06:37:06 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/26 06:37:07 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_LIB_DEFINE_H
# define NM_OTOOL_LIB_DEFINE_H

# include "nm_otool_lib_func.h"

# define OPT_WALL_MAX				0xffffffffffffffff
# define ASSIGN_BIT(x)				((1L << x))
# define VALUE_ALPHA_BIT(x)			((x < 97) ? x - 65 : x - 97 + 26)
# define SET_OPTS					1
# define XOR_OPTS					2
# define SUPR_OPTS					4
# define LAST_OPTS					8

#endif
