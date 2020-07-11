/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ot_handle_archive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 04:45:20 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 04:45:25 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int			set_archi_obj(void *file)
{
	struct ar_hdr	*header;
	int				size;
	char			*name;

	header = file;
	size = get_size_archive((char *)header);
	name = get_archive_name(file);
	get_ot_env(NULL)->archi_name = name;
	if (!ft_strstr(name, SYMDEF))
		archi_((void *)file + sizeof(*header) + size);
	ot_destroy_env(get_ot_env(NULL), OT_LET_NAME);
	return (1);
}

static void			set_arch_name(void)
{
	get_ot_env(NULL)->file_type ? free(get_ot_env(NULL)->file_type) : 0;
	get_ot_env(NULL)->file_type = ft_strjoin("Archive : ",
		get_ot_env(NULL)->exe_name);
	ft_putendl(get_ot_env(NULL)->file_type);
}

static int			handle_arch_loop(struct ar_hdr *header,
	unsigned int pad, void *obj)
{
	if (is_opt_set(get_ot_env(NULL)->opts, 'a'))
		display_header(header);
	header = (void *)obj + pad;
	while ((void *)header < get_ot_env(NULL)->file + get_ot_env(NULL)->size)
	{
		if (is_opt_set(get_ot_env(NULL)->opts, 'a'))
			display_header(header);
		else
			set_archi_obj((void *)header);
		header = (void *)header + sizeof(*header) + ft_atoi(header->ar_size);
	}
	get_ot_env(NULL)->arch_enabled = 0;
	return (EXIT_SUCCESS);
}

int					ot_handle_archive(void *data)
{
	struct ar_hdr	*header;
	struct ranlib	*obj;
	unsigned int	size;
	unsigned int	j;

	if (check_valid_file(data, SARMAG))
		return (ot_display_err(NULL, OT_NO_HD));
	header = (void *)data + SARMAG;
	size = (unsigned int)get_size_archive((char *)header);
	if (!size)
		return (ot_display_err(NULL, OT_NO_HDAR));
	if (check_valid_file((void *)header, sizeof(*header) + size))
		return (ot_display_err(NULL, OT_NO_HDAR));
	size = *(unsigned int *)((void *)header + sizeof(*header) + size);
	if (check_valid_file((void *)header, sizeof(*header)
		+ (unsigned int)get_size_archive((char *)header) + 4))
		return (ot_display_err(NULL, OT_NO_OBJAR));
	obj = (void *)header + sizeof(*header)
		+ (unsigned int)get_size_archive((char *)header) + 4;
	j = *(unsigned int *)((void *)obj + size);
	set_arch_name();
	return (handle_arch_loop(header, size + j + 4, (void *)obj));
}
