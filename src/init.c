/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:54:39 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 20:26:30 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** @brief Inicializa s_philo, un arreglo de filósofos.
**
** - Cada filósofo tiene dos tenedores que son su propio
** tenedor a la izquierda + el tenedor de su vecino a la derecha:
**
** 		i-1	  i		  	i
** 		RFork Filósofos LFork
** 		---------------------
** 		  P2  ← P0 →    P0 (tenedor propio a la izquierda)
** 		  P0  ← P1 →    P1 (tenedor propio a la izquierda)
** 		  P1  ← P2 →    P2 (tenedor propio a la izquierda)
** 		Donde F0 pertenece al filósofo P3.
**
** @param[in] philo un puntero a la estructura s_philo establecido en NULL.
** @param[in] data un puntero a una estructura s_data inicializada.
** @return    0 si todo salió bien, de lo contrario, 1.
*/

int	ft_init_philo(t_philo **philo, t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc (sizeof (pthread_mutex_t) * ((size_t)data->philo_nb));
	if (fork == NULL)
		return (FAILURE);
	i = 0;
	while (i < data->philo_nb)
		pthread_mutex_init (&fork[i++], NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].last_meal = data->simbegin;
		(*philo)[i].meals_counter = 0;
		(*philo)[i].lfork = i;
		if (i - 1 < 0)
			(*philo)[i].rfork = data->philo_nb - 1;
		else
			(*philo)[i].rfork = i - 1;
		(*philo)[i].fork = fork;
		(*philo)[i].data = data;
		i++;
	}
	return (SUCCESS);
}

/*
** @brief	  Inicializa s_data, los mutex del simulador.
**
** Para facilitar la adición de un mutex sin perder legibilidad a pesar
** del arreglo, la cantidad de mutex y sus nombres se definen en el archivo de encabezado.
**
** @param[in] data un puntero a una estructura s_data inicializada.
** @return 	  0 si todo salió bien, de lo contrario, 1.
*/

int	ft_init_data_mutexes(t_data **data)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = malloc (sizeof (pthread_mutex_t) * ((size_t)M_NUM));
	if (mutex == NULL)
		return (FAILURE);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_init (&mutex[i++], NULL);
	(*data)->mutex = mutex;
	return (SUCCESS);
}

/*
** @brief Inicializa s_data, los datos del simulador.
**
** Optimiza el patrón "escalera" del visualizador:
**
** Si philo_nb % 2 y time_eat > time_slp
** time_thk = 1 + time_eat - time_slp
**
** @param[in] data un puntero a la estructura s_data establecido en NULL.
** @param[in] ac el número de argumentos proporcionados al inicio del programa.
** @param[in] av los argumentos proporcionados al inicio del programa.
** @return    0 si todo salió bien, de lo contrario, 1.
*/

int	ft_init_data(t_data **data, int ac, char const *const *av)
{
	(*data)->simbegin = ft_abs_time ();
	(*data)->philo_nb = (int)ft_atol (av[1]);
	(*data)->time_die = (int)ft_atol (av[2]);
	(*data)->time_eat = (int)ft_atol (av[3]);
	(*data)->time_slp = (int)ft_atol (av[4]);
	(*data)->time_thk = 0;
	if (((*data)->philo_nb % 2) && ((*data)->time_eat > (*data)->time_slp))
		(*data)->time_thk = 1 + ((*data)->time_eat - (*data)->time_slp);
	if (ac == 5)
		(*data)->must_eat = -1;
	if (ac == 6)
		(*data)->must_eat = (int)ft_atol (av[5]);
	(*data)->done = FALSE;
	(*data)->died = FALSE;
	if (ft_init_data_mutexes (data))
		return (FAILURE);
	return (SUCCESS);
}

/*
** @brief     Inicializa las estructuras.
**
** @param[in] philo un puntero a la estructura s_philo establecido en NULL.
** @param[in] data un puntero a la estructura s_data establecido en NULL.
** @param[in] ac el número de argumentos proporcionados al inicio del programa.
** @param[in] av los argumentos proporcionados al inicio del programa.
** @return    0 si todo salió bien, de lo contrario, 1.
*/

int	ft_init(t_philo **philo, t_data **data, int ac, char const *const *av)
{
	*data = (t_data *)malloc (sizeof (t_data));
	if (*data == NULL)
		return (FAILURE);
	(*data)->mutex = NULL;
	if (ft_init_data (data, ac, av) != SUCCESS)
		return (FAILURE);
	*philo = (t_philo *)malloc (sizeof (t_philo) * (size_t)(*data)->philo_nb);
	if (*philo == NULL)
		return (FAILURE);
	(*philo)->fork = NULL;
	if (ft_init_philo (philo, *data) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}