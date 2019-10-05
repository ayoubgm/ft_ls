/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:49:59 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/05 00:51:18 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_files(t_dir_content *content, t_ls *ls, t_dir *dir)
{
	t_dir_content *tmp;

	ls->new_line = dir && content;
	tmp = content;
	ls->max_col = (t_dir_max_col){{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0};
	while (tmp)
	{
		get_max_cols(tmp, ls);
		tmp = tmp->next;
	}
	while (content)
	{
		print_data(content, ls);
		tmp = content;
		content = content->next;
		free_content(tmp, 1);
	}
}

t_dir_content *filter_content(t_dir_content *content, t_ls *ls)
{
	t_dir_content *head;
	t_dir_content *last;
	t_dir_content *tmp;
	DIR *dirp;

	head = NULL;
	while (content)
	{
		tmp = content->next;
		if (content->type == 0 && !(dirp = opendir(content->name)))
		{
			print_error(content->name, ls);
			free_content(content, 1);
		}
		else
			add_content(&head, &last, content);
		content = tmp;
	}
	return (head);
}

static t_dir *get_dirs(t_dir_content *content, t_ls *ls)
{
	t_dir_content *tmp;
	t_dir_content *head;
	t_dir_content *last;
	t_dir *dir;

	dir = NULL;
	head = NULL;
	content = filter_content(content, ls);
	while (content)
	{
		tmp = content;
		content = content->next;
		if (tmp->type == 4 || (tmp->type == 10 && !ft_flag_active('l', ls->flags)))
		{
			if (!new_dir(&dir))
			{
				set_error(ls, content, dir);
				exit(0);
			}
			dir->last_dir->path = ft_strdup(tmp->name);
			free_content(tmp, 1);
		}
		else
			add_content(&head, &last, tmp);
	}
	print_files(head, ls, dir);
	return (dir);
}

static int init(t_ls *ls, int ac, char *av[])
{
	int i;
	int f;

	i = 1;
	if (!(ls->dirs = (t_dir *)ft_memalloc(sizeof(t_dir))))
		exit(1);
	ls->tmp_dirs = ls->dirs;
	ft_memset(ls->spaces, ' ', 256);

	while (i < ac && (f = ft_set_flags(av[i], &ls->flags, LS_FLAGS)) > 0)
		i++;
	if (f == -1)
	{
		write(1, "ls: illegal option\n", 19);
		write(1, "usage: ./ft_ls [-URlTarfSuits] [file ...]\n", 43);
		exit(1);
	}
	return (i);
}

int main(int ac, char *av[])
{
	int i;
	t_ls ls;

	ft_bzero(&ls, sizeof(t_ls));
	i = init(&ls, ac, av);
	ls.nb_arg = ac - i;
	if (ac == i)
		ls.dirs->path = ft_strdup(".");
	else
	{
		while (i < ac)
		{
			if (!new_dir_content(ls.dirs))
				exit(0);
			ls.dirs->last_content->name = ft_strdup(av[i]);
			get_data("", ls.dirs->last_content, &ls);
			i++;
		}
		if (!ft_flag_active('f', ls.flags))
			ls.dirs->content = sort_content(ls.dirs->content, ls.nb_arg, &ls);
		ls.dirs = get_dirs(ls.dirs->content, &ls);
		free(ls.tmp_dirs);
	}
	dir_itirate(ls.dirs, &ls);
	write(1, ls.buff, ls.posbuff);
	return (0);
}
