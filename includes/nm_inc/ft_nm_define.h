/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_define.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 09:13:42 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/25 09:13:43 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_DEFINE_H
# define FT_NM_DEFINE_H

# include "ft_nm_func.h"

# define OPT_LIST		"AopnruUj"
# define NM_NO_FILE		"Permission denied"
# define NM_FSTAT_FAIL	"Fstat() call failed."
# define NM_MMAP_FAIL	"Mmap() call failed."
# define NM_MUNM_FAIL	"Munmap() call failed."
# define NM_NO_MAGIC	"is not an object file"
# define NM_NO_SYM		"Symbolic table not found."
# define NM_MALLOC_FAIL	"Malloc failed."
# define NM_NO_ARCH		"!<arch> Files are not supported."
# define NM_DIR			"Is a directory."
# define NM_NO_HD		"File is probably corrupted (header)."
# define NM_NO_FATHD	"File is probably corrupted (fat header)."
# define NM_NO_FATAR	"File is probably corrupted (fat arch)."
# define NM_NO_AROFF	"File is probably corrupted (fat arch offset)."
# define NM_NO_HDAR		"File is probably corrupted (header archive)."
# define NM_NO_LC		"File is probably corrupted (load commands)."
# define NM_NO_SYMCMD	"File is probably corrupted (symtab command)."
# define NM_NO_STRTAB	"File is probably corrupted (stringtable)."
# define NM_NO_SYMTAB	"File is probably corrupted (symbol table)."
# define NM_NO_SEG		"File is probably corrupted (segment command)."
# define NM_NO_SEC		"File is probably corrupted (sections)."
# define NM_NO_OBJAR	"File is probably corrupted (archive symdef)."
# define NM_NO_AROBJ	"File is probably corrupted (archive objects)."

# define NM_POWER_PC	1
# define NM_POWER_PC_64	2
# define NM_X86			4
# define NM_X86_64		8
# define NM_I386		16

# define NM_LET_NAME	1
# define NM_DESTROY		2

# define NM_PPC_PRINT	"for architecture ppc"
# define NM_I386_PRINT	"for architecture i386"

# define NM_32_PAD		"         "
# define NM_64_PAD		"                 "

#endif
