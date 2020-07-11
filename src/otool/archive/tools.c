/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 04:33:43 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/10 04:33:44 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char				*get_archive_name(void *file)
{
	return (ft_strdup((char *)file + sizeof(struct ar_hdr)));
}

int					get_size_archive(char *name)
{
	int				x;
	char			*word;

	word = ft_strchr(name, '/') + 1;
	if (!word)
		return (0);
	x = ft_atoi(word);
	return (x);
}
