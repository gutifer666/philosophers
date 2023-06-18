/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:24:46 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 21:13:37 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


/*
** @brief     Convertir una cadena numérica a un valor entero largo.
**
** @param[in] str la cadena numérica a convertir.
** @return    un valor entero largo.
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
** @brief     Valor máximo.
**
** @param[in] a un valor.
** @param[in] b otro valor distinto.
** @return    El valor más grande.
*/

int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

/*
** @brief     Valor mínimo.
**
** @param[in] a un valor.
** @param[in] b otro valor distinto.
** @return    El valor más pequeño.
*/

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
