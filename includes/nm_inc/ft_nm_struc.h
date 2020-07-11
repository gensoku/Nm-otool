/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_struc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 09:15:19 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/25 09:15:20 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_STRUC_H
# define FT_NM_STRUC_H

# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <ranlib.h>
# include "nm_otool_lib.h"
# include <ar.h>

typedef struct			s_section
{
	char				*name;
	unsigned int		id;
	struct s_section	*next;
}						t_section;

typedef struct			s_table
{
	char				type;
	unsigned long		value;
	char				*name;
	char				show;
	char				archi;
	char				debug;
	struct s_table		*next;
}						t_table;

typedef struct			s_nm_env
{
	unsigned long		opts;
	unsigned int		curr_archi;
	unsigned long		size;
	void				*addr;
	char				*exe_name;
	char				*archi_name;
	char				print_path;
	char				fat_enabled;
	char				arch_enabled;
	t_section			*sections;
	t_table				*tables;
}						t_nm_env;

#endif
