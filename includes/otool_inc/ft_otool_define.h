/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_define.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:36:42 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 03:36:43 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_DEFINE_H
# define FT_OTOOL_DEFINE_H

# include "ft_otool_func.h"

# define OPT_LIST		"thdfa"
# define OT_NO_FILE		"Permission denied"
# define OT_FSTAT_FAIL	"Fstat() call failed."
# define OT_MMAP_FAIL	"Mmap() call failed."
# define OT_MUOT_FAIL	"Munmap() call failed."
# define OT_NO_MAGIC	"is not an object file"
# define OT_NO_SYM		"Symbolic table not found."
# define OT_MALLOC_FAIL	"Malloc failed."
# define OT_NO_ARCH		"!<arch> Files are not supported."
# define OT_DIR			"Is a directory."
# define OT_NO_HD		"File is probably corrupted (header)."
# define OT_NO_FATHD	"File is probably corrupted (fat header)."
# define OT_NO_FATAR	"File is probably corrupted (fat arch)."
# define OT_NO_AROFF	"File is probably corrupted (fat arch offset)."
# define OT_NO_HDAR		"File is probably corrupted (header archive)."
# define OT_NO_LC		"File is probably corrupted (load commands)."
# define OT_NO_SYMCMD	"File is probably corrupted (symtab command)."
# define OT_NO_STRTAB	"File is probably corrupted (stringtable)."
# define OT_NO_SYMTAB	"File is probably corrupted (symbol table)."
# define OT_NO_SEG		"File is probably corrupted (segment command)."
# define OT_NO_SEC		"File is probably corrupted (sections)."
# define OT_NO_OBJAR	"File is probably corrupted (archive symdef)."
# define OT_NO_AROBJ	"File is probably corrupted (archive objects)."

# define LITTLE_END		1
# define BIG_END		2

# define OT_POWER_PC	1
# define OT_POWER_PC_64	2
# define OT_X86			4
# define OT_X86_64		8
# define OT_I386		16

# define ARGS_EXIT		100

# define GET_OT			(get_ot_env(NULL))

# define OT_LET_NAME	1
# define OT_DESTROY		2

# define OT_PPC_PRINT	"for architecture ppc"
# define OT_I386_PRINT	"for architecture i386"

# define OT_32_PAD		"         "
# define OT_64_PAD		"                 "

# define OT_SEC_TEXT	"Contents of (__TEXT,__text) section\n"
# define OT_SEC_DATA	"Contents of (__DATA,__data) section\n"

# define SUB_TYPE_MASK	0x000000ff

#endif
