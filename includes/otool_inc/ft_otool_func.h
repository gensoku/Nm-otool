/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:37:05 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 03:37:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_FUNC_H
# define FT_OTOOL_FUNC_H

# include "ft_otool_struct.h"

t_ot_env	*get_ot_env(t_ot_env *env);
int			ot_display_err(char *content, char *err_type);
int			archi_(char *data);
int			ft_otool(const char *const_path, char *path);
int			ot_handle_32(void *data);
int			add_section_32(t_ot_env *env, struct section *sec);
int			ot_handle_32_big(void *data);
int			add_section_32_big(t_ot_env *env, struct section *sec);
int			ot_handle_64(void *data);
int			add_section_64(t_ot_env *env, struct section_64 *sec);
int			ot_handle_64_big(void *data);
int			add_section_64_big(t_ot_env *env, struct section_64 *sec);
int			ot_handle_archive(void *data);
void		ot_display_all(t_ot_env *env);
int			check_valid_file(void *data, size_t off);
void		ot_destroy_env(t_ot_env *env, char opt);
void		ot_display_hex(void *data, unsigned long size, unsigned long addr,
	int pad);
void		cpu_x86_32(unsigned int narch, struct fat_header *h, void *data,
	struct fat_arch *arch);
void		cpu_powerpc_32(unsigned int narch, void *data,
	struct fat_arch *arch);
int			cpu_x86_64_32(unsigned int f, void *data, struct fat_arch *arch);
int			handle_fat_32(void *data, unsigned int f);
void		cpu_powerpc_64(unsigned int narch, void *data,
	struct fat_arch_64 *arch);
int			cpu_x86_64_64(unsigned int f, void *data,
	struct fat_arch_64 *arch);
void		cpu_x86_64(unsigned int narch, struct fat_header *h,
	void *data, struct fat_arch_64 *arch);
int			handle_fat_64(void *data, unsigned int f);
void		ot_destroy_env(t_ot_env *env, char opt);
void		ot_display_hex_ppc(void *data, unsigned long size,
	unsigned long addr, int pad);
void		ot_display_h_l(t_ot_env *env);
void		ot_display_h_b(t_ot_env *env);
void		ot_display_sec(t_section *tmp, t_ot_env *env, int pad);
void		display_header(struct ar_hdr *header);
void		dis_name(t_ot_env *env);
char		*get_archive_name(void *file);
int			get_size_archive(char *name);
int			ot_display_err_fd(char *content, char *err_type, int fd);
int			ot_display_err_ret(char *content, char *err_type, int ret);

#endif
