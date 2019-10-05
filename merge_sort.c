/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:33:23 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/05 02:43:59 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir_content	*get_med(t_dir_content *content, int size)
{
	while (content && size--)
		content = content->next;
	return (content);
}

int				content_compare(t_dir_content *content,
											t_dir_content *content2, t_ls *ls)
{
	const int r = ft_flag_active('r', ls->flags) ? -1 : 1;
	long  d;
	
	d = 0;
	if (ft_flag_active('S', ls->flags))
		d = content2->propr[6].v._long - content->propr[6].v._long;
	else if (ft_flag_active('t', ls->flags))
		d = content2->time_s - content->time_s;
	return ((d != 0? SIGN(d) : ft_strcmp(content->name, content2->name)) * r);
}

/*
** node 0 : head, node[1] : last, node[2] : tmp
*/

t_dir_content	*sort(t_dir_content *content, t_dir_content *content2,
															int *size, t_ls *ls)
{
	t_dir_content	*node[3];

	node[0] = NULL;
	while (size[0] && size[1])
	{
		if (content_compare(content, content2, ls) <= 0 && size[0]--)
		{
			node[2] = content;
			content = content->next;
		}
		else if (size[1]--)
		{
			node[2] = content2;
			content2 = content2->next;
		}
		node[0] ? (node[1]->next = node[2]) : 
												(node[1] = node[2]);
		node[0] ? (node[1] = node[1]->next) : 
												(node[0] = node[2]);
	}
	size[0] ? (node[1]->next = content) :
										(node[1]->next = content2);
	size[0] == 1 || size[1] == 1 ? (node[1]->next->next = NULL) : 0;
	return (node[0]);
}

void			*sort_content(t_dir_content *content, int size, t_ls *ls)
{
	int				size2;
	t_dir_content	*content2;
	
	size2 = size - (size / 2);
	if (size > 2)
	{
		size = size / 2;
		content2 = get_med(content, size);
		content = sort_content(content, size, ls);
		content2 = sort_content(content2, size2, ls);
		content = sort(content, content2, (int[2]){size, size2}, ls);
	}
	else if (size == 2)
	{
		size = size / 2;
		content = sort(content, content->next, (int[2]){size, size2}, ls);
	}
	return (content);
}
