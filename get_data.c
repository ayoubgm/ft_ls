/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:46:11 by gayoub            #+#    #+#             */
/*   Updated: 2019/10/04 23:23:07 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_permitions(mode_t mode, t_ls *ls)
{
	char permis[10];
	const char file_symbol[] = ".pc.d.b.-.l.s.";
	const char  per[] = "-rwxst";
	int i;
	int n;

	i = 1;
	n = 0;
	permis[0] = file_symbol[mode >> 12];
	while(i < 9) 
	{
		permis[i++] = per[((mode & (S_IRUSR >> n)) != 0) * 1];
		permis[i++] = per[((mode & (S_IWUSR >> n)) != 0) * 2];
		if (!(mode & S_IXUSR >> n) && (mode & (S_ISUID >> (n / 3))) != 0)
			permis[i] = i < 7 ? 'S' : 'T';
		else
			permis[i] = per[(((mode & (S_IXUSR >> n)) != 0) * 3)
						+ ((mode & (S_ISUID >> (n / 3))) != 0) * (1 + (i > 7))];
		i++;
		n += 3;
	}
	ft_write(permis, 10, ls);
	ft_write("  ", 2, ls);
}

void get_max_cols(t_dir_content *content, t_ls *ls)
{
	_Bool *active_prope;
	int i;

	i = 1;
	active_prope = (_Bool[10]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	if (ft_flag_active('l', ls->flags))
		active_prope = (_Bool[10]){1, 0, 0, 1, 1, 1, 1, 1, 1, 1};
	if (ft_flag_active('i', ls->flags))
		active_prope[2] = 1;
	if (ft_flag_active('s', ls->flags))
		active_prope[1] = 1;
	while (i < 9)
	{
		if (active_prope[i])
		{
			if(i != 4 && i != 5)
			content->propr[i].len = ft_declen(content->propr[i].v._long);
			if (ls->max_col.lens[i] < content->propr[i].len)
				ls->max_col.lens[i] = content->propr[i].len;
		}
		i++;
	}
	ls->max_col.total += content->propr[1].v._long;
}

void set_date(t_dir_content *content, struct stat *buff, t_ls *ls)
{
	if (ft_flag_active('u', ls->flags))
		content->time_s = buff->st_atimespec.tv_sec;
	else if (ft_flag_active('U', ls->flags))
		content->time_s = buff->st_birthtimespec.tv_sec;
	else
		content->time_s = buff->st_mtimespec.tv_sec;
}

_Bool stock_data(t_dir_content *content, struct stat *buff, t_ls *ls)
{
	content->type = buff->st_mode >> 12;
	ls->cb_file_exist |= content->type == DT_BLK || content->type == DT_CHR;
	if (ft_flag_active('i', ls->flags))
		content->propr[2].v._long = buff->st_ino;
	if (ft_flag_active('s', ls->flags) || ft_flag_active('l', ls->flags))
		content->propr[1].v._long = buff->st_blocks;
	if (ft_flag_active('l', ls->flags))
	{
		content->propr[0].v._long = buff->st_mode;
		content->propr[3].v._long = buff->st_nlink;
		content->propr[4].v._long = buff->st_uid;
		content->propr[5].v._long = buff->st_gid;
		content->propr[4].len = ft_strlen(getpwuid(buff->st_uid)->pw_name);
		content->propr[5].len = ft_strlen(getgrgid(buff->st_gid)->gr_name);
		content->propr[6].v._long = buff->st_size;
		if (ls->cb_file_exist)
		{
			content->propr[7].v._long = major(buff->st_rdev);
			content->propr[8].v._long = minor(buff->st_rdev);
		}
		set_date(content, buff, ls);
	}
	return (1);
}

_Bool get_file_linkto(char *path, t_dir_content *content,size_t size)
{
	char *buff_link;
	
	size = size ? size + 1 : PATH_MAX + 1;
	if (!(buff_link = (char *)malloc(sizeof(char) * size)))
		return (0);
	content->propr[10].len = readlink(path, buff_link, size - 1);
	if (content->propr[10].len == -1)
	{
		perror("readlink");
		return(0);
	}
	content->propr[10].v._string = buff_link;
	return (1);
}

_Bool get_data(char *path, t_dir_content *content, t_ls *ls)
{
	struct stat buff;
	char *path_name;

	path_name = ft_strjoin(path, content->name);
	if (lstat(path_name, &buff))
	{
		ft_strdel(&path_name);
		return (0);
	}
	if (S_ISLNK(buff.st_mode) && !get_file_linkto(path_name, content, buff.st_size))
	{
		ft_strdel(&path_name);
		return (0);
	}
	ft_strdel(&path_name);
	stock_data(content, &buff, ls);
	get_max_cols(content, ls);
	return (1);
}

