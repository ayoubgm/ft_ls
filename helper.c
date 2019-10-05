/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:38:53 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/02 03:55:21 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void set_size_max_len(t_ls *ls)
{
    ls->max_col.lens[10] = ls->max_col.lens[7] + ls->max_col.lens[8] + 2;
    if (ls->cb_file_exist)
        ls->max_col.lens[6] = ft_max(ls->max_col.lens[6], ls->max_col.lens[10]);
}

char *get_full_path(char *path)
{
    if (path[0] != '/' || path[1] != 0)
        path = ft_strjoin(path, "/");
    else
        path = ft_strdup(path);
    return (path);
}

void add_content(t_dir_content **head, t_dir_content **last, t_dir_content *content)
{
	*head ? ((*last)->next = content) : 0;
	*last = *head ? (*last)->next : content;
	*head ? 0 : (*head = content);
	(*last)->next = NULL;
}
