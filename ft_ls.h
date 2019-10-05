/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gayoub <gayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:50:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/05 14:52:56 by gayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FS_LS_H

# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <limits.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# define BUFF 4000
# define LS_FLAGS "URlGrafTSuits"

typedef struct	s_dir_max_col
{
	int						lens[11];
	int						total;
}				t_dir_max_col;

typedef struct	s_dir
{
	struct s_dir_content	*content;
	struct s_dir_content	*last_content;
	struct s_dir 			*last_dir;
	struct s_dir 			*next;
	char 					*path;
	int						content_size;

}				t_dir;

typedef union	u_propr_value
{
	char	*_string;
	long	_long;
} 				t_propr_value;

typedef struct	s_content_proprtiese 
{
	t_propr_value	v;
	int				len;
}				t_content_proprtiese;

/*
** 0: char* permition, 1: long  block, 2: long  inode, 3: long  links, 4: char* user,
** 5: char* group, 6: long  size, 7: long  major, 8: long  minor, 9: char* date 
*/
typedef struct	s_dir_content
{
	t_content_proprtiese	propr[11];
	char					*name;
	char 					type;
	struct s_dir_content	*next;
	long					time_s;
	long 					time_ns;
	int 					namelen;
}				t_dir_content;

typedef struct	s_ls
{	
	__uint128_t				flags;
	t_dir_max_col			max_col;
	t_dir					*dirs;
	t_dir					*tmp_dirs;
	char					buff[BUFF];
	char					spaces[256];
	int						posbuff;
	int						nb_arg;
	_Bool					has_error;
	_Bool					cb_file_exist;
	_Bool					new_line;
	
}				t_ls;

_Bool			new_dir_content(t_dir *dir);
_Bool			new_dir(t_dir **dir);
void 			dir_itirate(t_dir *dir, t_ls *ls);
void 			list_dir(t_dir *dir, t_ls *ls);
t_dir			*iter_dir_content(const char *path, t_dir_content *content, t_ls *ls);
_Bool			get_data(char *path, t_dir_content *content, t_ls *ls);
void			print_data(t_dir_content *content, t_ls *ls);
void			print_content(t_dir_content *content, t_ls *ls, int propid);
void			print_date(t_dir_content *content, t_ls *ls);
void			print_total(t_ls *ls);
void			print_error(const char *file_name, t_ls *ls);
void			print_dir_path(const char *path, t_ls *ls);
void			*sort_content(t_dir_content *content, int size, t_ls *ls);
void			ft_write(const char *s, size_t len, t_ls *ls);
void			ft_putnbr2(long nb, t_ls *ls);
void			set_size_max_len(t_ls *ls);
char			*get_full_path(char *path);
void			add_content(t_dir_content **head, t_dir_content **last, t_dir_content *content);
void			get_max_cols(t_dir_content *content, t_ls *ls);
void			set_error(t_ls *ls, t_dir_content *content, t_dir *dir);
void			free_dir(t_dir *dir, int nb);
void			free_content(t_dir_content *content, int nb);
void			print_permitions(mode_t mode, t_ls *ls);
void			print_with_colors(t_dir_content *content, t_ls *ls);
void			reset_colors(t_ls *ls);

#endif
