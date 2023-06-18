/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:33:47 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 20:31:05 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** @brief     Libera toda la memoria asignada dinámicamente por el programa.
**
** @param[in] philo la estructura de la simulación.
** @param[in] data la estructura del simulador.
*/

static void	ft_clear_memory(t_philo *philo, t_data *data)
{
	if (data && data->mutex)
		free (data->mutex);
	if (data)
		free (data);
	if (philo && philo->fork)
		free (philo->fork);
	if (philo)
		free (philo);
}

/*
** @brief     Maneja casos límite.
**
** Si el parámetro 'must_eat' se establece en 0. O si solo hay un
** filósofo.
**
** @param[in] ac el número de argumentos proporcionados al inicio del programa.
** @param[in] av los argumentos proporcionados al inicio del programa.
** @return    1 si no hay casos límite coincidentes, de lo contrario, 0.
*/

static int	ft_edgecases(int ac, char const *const *av)
{
	if ((ac == 6 && ft_atol (av[5]) == 0))
		return (TRUE);
	if (ft_atol (av[1]) == 0)
		return (TRUE);
	return (FALSE);
}

/*
** @brief     Iniciar y finalizar el programa.
**
** Información de entrada:
** ./philo philo_nb time_die time_eat time_slp [ must_eat ]
** Ejemplo: ./philo 4 410 200 200 7
**
** @param[in] ac el número de argumentos proporcionados al inicio del programa.
** @param[in] av los argumentos proporcionados al inicio del programa.
** @return    0 si todo salió bien, de lo contrario, 1.
*/

int	main(int ac, char const *const *av)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	philo = NULL;
	if (ft_check_args (ac, av) != SUCCESS)
		return ((void)ft_clear_memory (philo, data), EXIT_FAILURE);
	if (ft_edgecases (ac, av))
		return ((void)ft_clear_memory (philo, data), EXIT_SUCCESS);
	if (ft_init (&philo, &data, ac, av) != SUCCESS)
		return ((void)ft_clear_memory (philo, data), EXIT_FAILURE);
	if (ft_simulator (philo, data) != SUCCESS)
		return ((void)ft_clear_memory (philo, data), EXIT_FAILURE);
	return ((void)ft_clear_memory (philo, data), EXIT_SUCCESS);
}