/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:39:51 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 20:57:34 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** @brief    El filósofo toma los tenedores.
**
** - Utilizando una "jerarquía de bloqueo" para prevenir bloqueos.
** - Maneja el caso de 'un solo filósofo' asegurándose de que no haya solo un tenedor en
** la mesa: 'lfork == rfork'.
**
** @param[in] self los datos del filósofo.
** @return    0 si todo salió bien, de lo contrario, 1.
*/

static int	ft_start_eating(t_philo *self)
{
	pthread_mutex_lock (&self->fork[ft_min (self->lfork, self->rfork)]);
	ft_print (self, "has taken a fork");
	if (self->lfork == self->rfork)
	{
		pthread_mutex_unlock (&self->fork[ft_min (self->lfork, self->rfork)]);
		return (FAILURE);
	}
	pthread_mutex_lock (&self->fork[ft_max (self->lfork, self->rfork)]);
	ft_print (self, "has taken a fork");
	ft_print (self, "is eating");
	return (SUCCESS);
}

/*
** @brief     El filósofo suelta los tenedores y duerme.
**
** Imprimimos "está durmiendo" antes de soltar los tenedores y dormimos después de soltarlos
** para asegurarnos de que "está durmiendo" se imprima justo después de "está comiendo".
**
** @param[in] self los datos del filósofo.
** @return 0  si todo salió bien.
*/

static int	ft_finish_eating(t_philo *self)
{
	ft_print (self, "is sleeping");
	pthread_mutex_unlock (&self->fork[ft_max (self->lfork, self->rfork)]);
	pthread_mutex_unlock (&self->fork[ft_min (self->lfork, self->rfork)]);
	ft_msleep (self->data->time_slp);
	return (SUCCESS);
}

/*
** @brief     Comida del filósofo.
**
** - Una comida se considera como +1 comida tan pronto como comienza. Incluso si
** ya se consideran como 'terminados', los filósofos que comenzaron a comer deben
** terminar adecuadamente de comer pasando por 'time_eat'.
**
** @param[in] self los datos del filósofo.
** @return    0 si todo salió bien, de lo contrario, 1.
*/

static int	ft_eating(t_philo *self)
{
	if (ft_start_eating (self) != SUCCESS)
		return (FAILURE);
	pthread_mutex_lock (&self->data->mutex[MEALS]);
	self->last_meal = ft_abs_time ();
	self->meals_counter++;
	pthread_mutex_unlock (&self->data->mutex[MEALS]);
	if (ft_check_done (self))
	{
		ft_finish_eating (self);
		return (FAILURE);
	}
	ft_msleep (self->data->time_eat);
	ft_finish_eating (self);
	return (SUCCESS);
}

/*
** @brief     Ciclo de vida del filósofo.
**
** - Incluso los filósofos están retardados para prevenir cualquier conflicto durante el momento de tomar los tenedores.
**
** XXX
** Pasar de ft_msleep (que contiene un bucle while usleep(10)) a usleep me hizo pasar del 700% de uso de CPU a <20%.
**
** @param[in] arg los datos del filósofo.
** @return    Un puntero NULL.
*/

void	*ft_simulation(void *arg)
{
	t_philo	*self;

	self = (t_philo *) arg;
	if (self->id % 2 == 0)
	{
		ft_print (self, "is thinking");
		ft_msleep (self->data->time_eat);
	}
	while (1)
	{
		if (ft_check_died(self))
			break ;
		if (ft_eating (self) != SUCCESS)
			break ;
		ft_print (self, "is thinking");
		ft_msleep (self->data->time_thk);
	}
	return (NULL);
}