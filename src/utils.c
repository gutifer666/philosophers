/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:24:46 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 10:46:04 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
 ** @brief      Convert a numerical string to a long integer value.
 **
 ** @param[in]  str the numerical string to convert.
 ** @return     a long integer value.
 */

long	ft_atol(char const *str)
{
	long	sign;
	long	nb;

	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nb = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

/*
 ** @brief      Max value.
 **
 ** @param[in]  a a value.
 ** @param[in]  b a different another value.
 ** @return     The biggest value.
 */

int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

/*
 ** @brief      Min value.
 **
 ** @param[in]  a a value.
 ** @param[in]  b a different value.
 ** @return     The smallest value.
 */

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
