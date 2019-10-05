/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 00:34:04 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/04 22:55:18 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ft_write(const char *s, size_t len, t_ls *ls)
{
    size_t i;

    i = 0;
    while(s && i < len)
    { 
        if(ls->posbuff == BUFF)
        {
            write(1, ls->buff, BUFF);
            ls->posbuff = 0;
        }
        ls->buff[ls->posbuff++] = s[i++];
    }
}

void	ft_putnbr2(long nb, t_ls *ls)
{
	long	n;
    char    c;

	n = nb;
	if (n < 0)
	{
		ft_write("-" , 1, ls);
		n *= -1;
	}
	if (n > 9)
		ft_putnbr2(n / 10,ls);
    c = n % 10 + 48;
	ft_write(&c, 1, ls);
}

void    print_error(const char *file_name, t_ls *ls)
{
    char *str_error;

    if(!(str_error = ft_strjoin("ls: ", file_name)))
        return ;
    write(1,ls->buff,ls->posbuff);
    ls->posbuff = 0;
    perror(str_error);
    free(str_error);
}

void print_dir_path(const char *path, t_ls *ls)
{
    if (ls->nb_arg > 1)
    {
        if (ls->new_line)
            ft_write("\n", 1, ls);
        ft_write(path, ft_strlen(path) - !!path[1], ls);
        ft_write(":\n", 2, ls);
    }
    ls->new_line = 1;
    ls->nb_arg = 2;
}
