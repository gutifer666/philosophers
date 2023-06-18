/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:49:10 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 20:15:55 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** @brief		Verifica si una cadena es un valor numérico positivo.
**
** @param[in] 	str la cadena a verificar.
** @return 		Verdadero o falso.
*/

static int	ft_is_numeric(char const *str)
{
	int	i;

	i = 0;
	if (*str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

/*
** @brief		Verifica si los argumentos proporcionados por el usuario son válidos.
**
** @param[in] 	ac el número de argumentos proporcionados al inicio del programa.
** @param[in] 	av los argumentos proporcionados al inicio del programa.
** @return 		0 si son válidos, de lo contrario, 1.
*/

int	ft_check_args(int ac, char const *const *av)
{
	if (ac < 5)
	{
		write (2, "Error: Too few arguments.\n", 26);
		return (FAILURE);
	}
	if (ac > 6)
	{
		write (2, "Error: Too many arguments.\n", 27);
		return (FAILURE);
	}
	while (ac-- > 1)
	{
		if (ft_is_numeric (av[ac]) == FALSE)
		{
			write (2, "Error: Invalid character.\n", 26);
			return (FAILURE);
		}
		if (ft_atol (av[ac]) > INT_MAX || ft_atol (av[ac]) < 0)
		{
			write (2, "Error: Out of range value.\n", 27);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}