/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 01:34:20 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/05 00:34:45 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int read_content(char *path, DIR *dirp, t_dir *dir, t_ls *ls)
{
	struct dirent *dp;
	t_dir_content *tmp;

	while ((dp = readdir(dirp)))
	{
		tmp = dir->last_content;
		if ((!ft_flag_active('a', ls->flags) && *dp->d_name == '.'))
			continue;
		if (!new_dir_content(dir))
			return (0);
		dir->last_content->name = malloc(dp->d_namlen + 1);
		ft_strcpy(dir->last_content->name, dp->d_name);
		dir->last_content->namelen = dp->d_namlen;
		if (!get_data(path, dir->last_content, ls))
		{
			free_content(dir->last_content, 1);
			dir->last_content = tmp;
			dir->content = tmp ? dir->content : tmp;
			dir->content_size--;
		}
		dir->content_size++;
	}
	if (!ft_flag_active('f', ls->flags))
		dir->content = sort_content(dir->content, dir->content_size, ls);
	return (1);
}

void dir_itirate(t_dir *dir, t_ls *ls)
{
	t_dir *tmp;

	while (dir && !ls->has_error)
	{
		list_dir(dir, ls);
		tmp = dir;
		dir = dir->next;
		free_dir(tmp, 1);
	}
	dir ? free_dir(dir, -1) : 0;
}

void list_dir(t_dir *dir, t_ls *ls)
{
	DIR *dirp;
	char *dir_path;

	ls->max_col = (t_dir_max_col){{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0};
	ls->cb_file_exist = 0;
	if (!(dir_path = get_full_path(dir->path)))
		return (set_error(ls, NULL, NULL));
	if ((dirp = opendir(dir->path)))
	{
		if (!read_content(dir_path, dirp, dir, ls))
		{
			closedir(dirp);
			return (set_error(ls, dir->content, NULL));
		}
		closedir(dirp);
		dir = iter_dir_content(dir_path, dir->content, ls);
		dir ? dir_itirate(dir, ls) : 0;
	}
	else
	{
		print_dir_path(dir_path, ls);
		print_error(ft_strrchr(dir->path, '/') + 1, ls);
	}
	ft_strdel(&dir_path);
}

t_dir *iter_dir_content(const char *path, t_dir_content *content, t_ls *ls)
{
	t_dir *dir;
	t_dir_content *tmp;

	dir = NULL;
	set_size_max_len(ls);
	print_dir_path(path, ls);
	content ? print_total(ls) : 0;
	while (content)
	{
		tmp = content;
		content = content->next;
		print_data(tmp, ls);
		if (tmp->type == DT_DIR && ft_flag_active('R', ls->flags))
			if (tmp->namelen > 2 || (!ft_strequ(".", tmp->name) && (!ft_strequ("..", tmp->name))))
			{
				if (!new_dir(&dir))
					exit(0);
				dir->last_dir->path = ft_strjoin(path, tmp->name);
			}
		free_content(tmp, 1);
	}
	return (dir);
}
