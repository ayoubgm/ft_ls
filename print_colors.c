/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gayoub <gayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:16:07 by gayoub            #+#    #+#             */
/*   Updated: 2019/10/05 15:44:20 by gayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void reset_colors(t_ls *ls)
{
  if (ft_flag_active('G', ls->flags))
        ft_write("\e[0m", 4, ls);
}

void print_with_colors(t_dir_content *content, t_ls *ls)
{
    if (ft_flag_active('G', ls->flags))
    {
        if (content->type == DT_DIR && content->propr[0].v._long & S_IWOTH &&
            content->propr[0].v._long & S_ISVTX)
            ft_write("\e[42;30m", 8, ls);
        else if (content->type == DT_DIR && content->propr[0].v._long & S_IWOTH)
            ft_write("\e[43;30m", 8, ls);
        else if (content->type == DT_DIR)
            ft_write("\e[1;96m", 7, ls);
        else if (content->type == DT_REG && (content->propr[0].v._long & S_IXUSR
                || content->propr[0].v._long & S_IXGRP
                || content->propr[0].v._long & S_IXOTH))
            ft_write("\e[31m", 5, ls);
        else if (content->type == DT_LNK)
            ft_write("\e[35m", 5, ls);
        else if (content->type == DT_CHR)
            ft_write("\e[43;34m", 8, ls);
        else if (content->type  == DT_BLK)
            ft_write("\e[106;34m", 9, ls);
        ft_write(content->name, content->namelen, ls);
        reset_colors(ls);
    }
    else
        ft_write(content->name, content->namelen, ls);
}