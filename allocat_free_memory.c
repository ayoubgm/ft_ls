/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocat_free_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 12:12:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/04 19:39:10 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

_Bool new_dir_content(t_dir *dir)
{
	t_dir_content *new_content;

	if (!(new_content = (t_dir_content *)ft_memalloc(sizeof(t_dir_content))))
		return (0);
	if (!dir->content)
		dir->content = new_content;
	if (dir->last_content)
		dir->last_content->next = new_content;
	dir->last_content = new_content;
	return (1);
}

_Bool new_dir(t_dir **dir)
{
	t_dir *new_dir;

	if (!(new_dir = (t_dir *)ft_memalloc(sizeof(t_dir))))
		return (0);
	if (*dir)
		(*dir)->last_dir->next = new_dir;
	else
		*dir = new_dir;
	(*dir)->last_dir = new_dir;
	return (1);
}

void free_content(t_dir_content *content, int nb)
{
	t_dir_content *tmp;
	while (content && nb--)
	{
		tmp = content;
		content = content->next;
		ft_strdel(&tmp->propr[10].v._string);
		ft_strdel(&tmp->name);
		ft_memdel((void **)&tmp);
	}
}

void free_dir(t_dir *dir, int nb)
{
	t_dir *tmp;
	
	while (dir && nb--)
	{
		tmp = dir;
		dir = dir->next;
		ft_strdel(&tmp->path);
		ft_memdel((void **)&tmp);
	}
}

void set_error(t_ls *ls, t_dir_content *content, t_dir *dir)
{
	ls->has_error = 1;
	free_content(content, -1);
	free_dir(dir,-1);
}
