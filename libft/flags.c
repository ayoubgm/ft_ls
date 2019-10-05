/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gayoub <gayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:32:07 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/01 17:10:41 by gayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void put_bit(__uint128_t *op, int n)
{
	__uint128_t b;

	b = 1;
	b <<= n;
	*op |= b;
}

char ft_set_flags(char *str, __uint128_t *flags,const char *accepted_flgs)
{
	if (!str || *str++ != '-' || !ft_isascii(*str))
		return (0);
	while (*str)
	{
		if (ft_isinstr(*str, accepted_flgs))
			put_bit(flags, *str);
		else if(!accepted_flgs && ft_isalnum(*str))
			put_bit(flags, *str);
		else
			return(-1);
		str++;
	}
	return (1);
}

_Bool ft_flag_active(char c, __uint128_t flags)
{
	return ((flags >> c) & 1);
}
