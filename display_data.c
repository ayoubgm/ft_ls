/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gayoub <gayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 04:35:42 by gayoub            #+#    #+#             */
/*   Updated: 2019/10/05 14:56:06 by gayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_size(t_dir_content *content, t_ls *ls)
{
    ls->cb_file_exist ? ft_write(" ", 1, ls) : 0;
    if (content->type == DT_BLK || content->type == DT_CHR)
    {
        ft_write(ls->spaces, ls->max_col.lens[7] - content->propr[7].len, ls);
        ft_putnbr2(content->propr[7].v._long, ls);
        ft_write(", ", 2, ls);
        ft_write(ls->spaces, ls->max_col.lens[6] - (ls->max_col.lens[7] + 2 + content->propr[8].len), ls);
        ft_putnbr2(content->propr[8].v._long, ls);
    }
    else
    {
        ft_write(ls->spaces, ls->max_col.lens[6] - content->propr[6].len, ls);
        ft_putnbr2(content->propr[6].v._long, ls);
    }
    ft_write(" ", 1, ls);
}

void print_total(t_ls *ls)
{
    if (ft_flag_active('l', ls->flags) || ft_flag_active('s', ls->flags))
    {
        ft_write("total ", 6, ls);
        ft_putnbr2(ls->max_col.total, ls);
        ft_write("\n", 1, ls);
    }
}

void print_date(t_dir_content *content, t_ls *ls)
{
    time_t curr_time;

    curr_time = time(NULL);
    content->propr[9].v._string = ctime(&content->time_s);
    if (ft_flag_active('T', ls->flags))
        ft_write(content->propr[9].v._string + 4, 20, ls);
    else if(content->propr[9].v._string)
    {
        ft_write(content->propr[9].v._string + 4, 7, ls);
        if ((curr_time - content->time_s) > 15770000)
            ft_write(content->propr[9].v._string + 19, 5, ls);
        else
            ft_write(content->propr[9].v._string + 11, 5, ls);
    }
     ft_write(" ", 1, ls);
}

void print_content(t_dir_content *content, t_ls *ls, int pid)
{
    char *string;

    if (pid == 4 || pid == 5)
    {
        if(pid == 4)
            string  = getpwuid(content->propr[pid].v._long)->pw_name;
        else if(pid == 5)
            string  = getgrgid(content->propr[pid].v._long)->gr_name;
        ft_write(string , content->propr[pid].len, ls);
        ft_write(ls->spaces, ls->max_col.lens[pid] - content->propr[pid].len, ls);
        ft_write(ls->spaces, 2, ls);
    }
    else
    {
        ft_write(ls->spaces, ls->max_col.lens[pid] - content->propr[pid].len, ls);
        ft_putnbr2(content->propr[pid].v._long, ls);
        ft_write(ls->spaces, 1, ls);
    }
}

void print_data(t_dir_content *content, t_ls *ls)
{
    int i;

    i = 3;
    if (ft_flag_active('i', ls->flags))
        print_content(content, ls, 2);
    if (ft_flag_active('s', ls->flags))
        print_content(content, ls, 1);
    if (ft_flag_active('l', ls->flags))
    {
        print_permitions(content->propr[0].v._long ,ls);
        while (i < 6)
            print_content(content, ls, i++);
        print_size(content, ls);
        print_date(content, ls);
    }
    print_with_colors(content, ls);
    if (content->type == DT_LNK)
    {
        ft_write(" -> ", 4, ls);
        ft_write(content->propr[10].v._string, content->propr[10].len, ls);
    }
    ft_write("\n", 1, ls);
}
