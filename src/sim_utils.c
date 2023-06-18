/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:38:03 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 20:47:07 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


/*
** @brief     Registrar las acciones del ciclo de vida de cada filósofo en la terminal.
**
** @param[in] philo la estructura de la simulación.
** @param[in] a la acción del filósofo.
*/

void	ft_print(t_philo *philo, char const *const a)
{
	pthread_mutex_lock (&philo->data->mutex[PRINT]);
	if (*a == 'd' || (!ft_check_died (philo) && !ft_check_done (philo)))
		printf("%lu %d %s\n", ft_rel_time(philo->data->simbegin), philo->id, a);
	pthread_mutex_unlock (&philo->data->mutex[PRINT]);
}

/*
** @brief     Oficializar la primera muerte.
**
** @param[in] data la estructura del simulador.
*/

void	ft_died(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DIED]);
	data->died = TRUE;
	pthread_mutex_unlock (&data->mutex[DIED]);
}

/*
** @brief     Oficializar el final de la cena.
**
** Todos los filósofos han comido al menos 'must_eat' veces.
**
** @param[in] data la estructura del simulador.
*/

void	ft_done(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DONE]);
	data->done = TRUE;
	pthread_mutex_unlock (&data->mutex[DONE]);
}

/*
** @brief     Verificar si ha ocurrido una muerte.
**
** @param[in] data la estructura del simulador.
*/

int	ft_check_died(t_philo *philo)
{
	pthread_mutex_lock (&philo->data->mutex[DIED]);
	if (philo->data->died)
	{
		pthread_mutex_unlock (&philo->data->mutex[DIED]);
		return (TRUE);
	}
	pthread_mutex_unlock (&philo->data->mutex[DIED]);
	return (FALSE);
}

/*
** @brief     Verificar si la cena ha finalizado.
**
** Todos los filósofos han comido al menos 'must_eat' veces.
**
** @param[in] data la estructura del simulador.
*/

int	ft_check_done(t_philo *philo)
{
	pthread_mutex_lock (&philo->data->mutex[DONE]);
	if (philo->data->done)
	{
		pthread_mutex_unlock (&philo->data->mutex[DONE]);
		return (TRUE);
	}
	pthread_mutex_unlock (&philo->data->mutex[DONE]);
	return (FALSE);
}