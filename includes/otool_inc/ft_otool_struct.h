/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:36:50 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 03:36:51 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_STRUCT_H
# define FT_OTOOL_STRUCT_H

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

typedef struct				s_section
{
	char					*name;
	unsigned int			id;
	unsigned long			size;
	unsigned int			offset;
	unsigned long			addr;
	struct s_section		*next;
}							t_section;

typedef struct				s_ot_env
{
	unsigned long			opts;
	unsigned int			curr_archi;
	unsigned long			size;
	struct mach_header_64	*hd;
	unsigned int			magic;
	int						archi;
	char					endian;
	void					*addr;
	void					*file;
	char					*exe_name;
	char					*archi_name;
	char					*file_type;
	char					print_path;
	char					fat_enabled;
	char					arch_enabled;
	t_section				*sections;
}							t_ot_env;

#endif
