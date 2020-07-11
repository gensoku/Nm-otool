/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 07:55:47 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/26 07:55:48 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

#include <stdio.h>

int						archi_(char *data)
{
	unsigned int		magic;

	magic = *(unsigned int *)data;
	if (magic == MH_MAGIC)
		return (nm_handle_32(data, 0));
	else if (magic == MH_MAGIC_64)
		return (nm_handle_64(data, 0));
	else if (magic == MH_CIGAM)
		return (nm_handle_32_big(data, 0, 0));
	else if (magic == MH_CIGAM_64)
		return (nm_handle_64_big(data, 0, 0));
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (handle_fat_32(data, 0, 0, 0));
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return (handle_fat_64(data, 0, 0));
	else if (ft_strlen(data) > 8 && !ft_strncmp((char *)data, ARMAG, 8))
		return (nm_handle_archive(data));
	return (nm_display_err(get_nm_env(NULL)->exe_name, NM_NO_MAGIC));
}

static int				path_free_ret(char *path)
{
	nm_display_err(path, NM_NO_FILE);
	ft_memdel((void **)&path);
	return (EXIT_FAILURE);
}

int						ft_nm(const char *const_path, char *path)
{
	int					fd;
	int					ret_code;
	struct stat			stat_buf;
	char				*data;

	path = ft_strdup(const_path);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (path_free_ret(path));
	if ((fstat(fd, &stat_buf)) < 0)
		return (nm_display_err(NULL, NM_FSTAT_FAIL));
	else if (stat_buf.st_mode & S_IFDIR)
		return (nm_display_err(get_nm_env(NULL)->exe_name, NM_DIR));
	else
		get_nm_env(NULL)->size = stat_buf.st_size;
	if ((data = mmap(0, stat_buf.st_size, PROT_READ,
		MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		return (nm_display_err(NULL, NM_MMAP_FAIL));
	}
	get_nm_env(NULL)->addr = data;
	ret_code = archi_(data);
	path ? ft_memdel((void **)&path) : 0;
	if (munmap(data, stat_buf.st_size) < 0)
		return (nm_display_err(NULL, NM_MUNM_FAIL));
	return (ret_code);
}
