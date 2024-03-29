/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_bits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 14:15:08 by souarrak          #+#    #+#             */
/*   Updated: 2019/06/19 22:18:26 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

__uint64_t	ft_reverse_bits(__uint64_t nb0, int n)
{
	__uint64_t	nb;
	int			i;

	i = 0;
	nb = 0;
	while (i++ < n)
	{
		nb <<= 1;
		nb ^= nb0 & 1;
		nb0 >>= 1;
	}
	return (nb);
}
