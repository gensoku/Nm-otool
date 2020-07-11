/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:46:37 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 03:46:38 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

#include <stdio.h>

int						archi_(char *data)
{
	unsigned int		magic;

	magic = *(unsigned int *)data;
	get_ot_env(NULL)->magic = magic;
	get_ot_env(NULL)->addr = data;
	if (magic == MH_MAGIC)
		return (ot_handle_32(data));
	else if (magic == MH_MAGIC_64)
		return (ot_handle_64(data));
	else if (magic == MH_CIGAM)
		return (ot_handle_32_big(data));
	else if (magic == MH_CIGAM_64)
		return (ot_handle_64_big(data));
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (handle_fat_32(data, 0));
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return (handle_fat_64(data, 0));
	else if (ft_strlen(data) > 8 && !ft_strncmp((char *)data, ARMAG, 8))
		return (ot_handle_archive(data));
	return (ot_display_err_fd(get_ot_env(NULL)->exe_name, OT_NO_MAGIC, 1));
}

static int				path_free_ret(char *path)
{
	ot_display_err(path, OT_NO_FILE);
	ft_memdel((void **)&path);
	return (ARGS_EXIT);
}

int						ft_otool(const char *const_path, char *path)
{
	int					fd;
	int					ret_code;
	struct stat			stat_buf;
	char				*data;

	path = ft_strdup(const_path);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (path_free_ret(path));
	if ((fstat(fd, &stat_buf)) < 0)
		return (ot_display_err(NULL, OT_FSTAT_FAIL));
	else if (stat_buf.st_mode & S_IFDIR)
		return (ot_display_err_ret(GET_OT->exe_name, OT_DIR, ARGS_EXIT));
	else
		get_ot_env(NULL)->size = stat_buf.st_size;
	if ((data = mmap(0, stat_buf.st_size, PROT_READ,
		MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		return (ot_display_err(NULL, OT_MMAP_FAIL));
	}
	get_ot_env(NULL)->file = data;
	ret_code = archi_(data);
	path ? ft_memdel((void **)&path) : 0;
	if (munmap(data, stat_buf.st_size) < 0)
		return (ot_display_err(NULL, OT_MUOT_FAIL));
	return (ret_code);
}
