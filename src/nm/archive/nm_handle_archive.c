/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_handle_archive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 08:39:18 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/12 08:39:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char			*get_ar_name(void *file)
{
	return (ft_strdup((char *)file + sizeof(struct ar_hdr)));
}

static int			get_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	if (!word)
		return (0);
	x = ft_atoi(word);
	return (x);
}

static int			set_archi_obj(void *file)
{
	struct ar_hdr	*header;
	int				size;
	char			*name;

	header = file;
	size = get_size((char *)header);
	name = get_ar_name(file);
	get_nm_env(NULL)->archi_name = name;
	if (!ft_strstr(name, SYMDEF))
		archi_((void *)file + sizeof(*header) + size);
	nm_destroy_env(get_nm_env(NULL), NM_LET_NAME);
	return (1);
}

static int			nm_handle_archive_loop(struct ar_hdr *header)
{
	get_nm_env(NULL)->print_path = 1;
	get_nm_env(NULL)->arch_enabled = 1;
	while ((void *)header < get_nm_env(NULL)->addr + get_nm_env(NULL)->size)
	{
		set_archi_obj((void *)header);
		header = (void *)header + sizeof(*header) + ft_atoi(header->ar_size);
	}
	get_nm_env(NULL)->arch_enabled = 0;
	return (EXIT_SUCCESS);
}

int					nm_handle_archive(void *data)
{
	struct ar_hdr	*header;
	struct ranlib	*obj;
	unsigned int	size;
	unsigned int	j;

	if (check_valid_file(data, SARMAG))
		return (nm_display_err(NULL, NM_NO_HD));
	header = (void *)data + SARMAG;
	size = (unsigned int)get_size((char *)header);
	if (!size)
		return (nm_display_err(NULL, NM_NO_HDAR));
	if (check_valid_file((void *)header, sizeof(*header) + size))
		return (nm_display_err(NULL, NM_NO_HDAR));
	size = *(unsigned int *)((void *)header + sizeof(*header) + size);
	if (check_valid_file((void *)header, sizeof(*header)
		+ (unsigned int)get_size((char *)header) + 4))
	{
		return (nm_display_err(NULL, NM_NO_OBJAR));
	}
	obj = (void *)header + sizeof(*header)
		+ (unsigned int)get_size((char *)header) + 4;
	j = *(unsigned int *)((void *)obj + size);
	header = (void *)obj + size + j + 4;
	return (nm_handle_archive_loop(header));
}
