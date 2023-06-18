/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:11:12 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/18 21:19:57 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/* portability */
# define _DEFAULT_SOURCE
# define _GNU_SOURCE
# define _BSD_SOURCE

/*
 ** =========[ Includes ]==========
 */

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

/*
 ** =========[ Enum ]==============
 */

/* Simulator's mutexes */

typedef enum e_mutexes
{
	PRINT,
	MEALS,
	DONE,
	DIED,
	M_NUM
}	t_mutexes;

/* Booleans */

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/* Exit codes */

typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

/*
 ** =========[ Structures ]========
 */


/*
** @brief Datos del simulador.
**
** @var		philo_nb 	el número de filósofos.
** @var		time_die 	el tiempo en milisegundos para que un filósofo muera.
** @var		time_eat 	el tiempo en milisegundos para que un filósofo coma.
** @var		time_slp 	el tiempo en milisegundos para que un filósofo duerma.
** @var 	time_thk 	el tiempo en milisegundos para que un filósofo piense.
** @var 	must_eat 	el número máximo de veces que cada filósofo debe comer.
**
** @var 	simbegin 	el tiempo del EPOCH cuando comienza la simulación.
** @var 	done 		es verdadero cuando todos los filósofos han comido must_eat veces, la simulación se detiene.
** @var 	died 		es verdadero cuando un filósofo ha muerto, la simulación se detiene.
** @var 	mutex 		un arreglo de mutex para las operaciones de la simulación.
*/

typedef struct s_data
{
	int					philo_nb;
	int					time_die;
	int					time_eat;
	int					time_slp;
	int					time_thk;
	int					must_eat;

	unsigned long		simbegin;
	int					done;
	int					died;
	pthread_mutex_t		*mutex;

}					t_data;


/*
** @brief 	Datos de la simulación.
**
** @var id 				 el nombre del filósofo.
** @var last_meal 		 el tiempo del EPOCH de la última comida consumida.
** @var meals_counter 	 el número de comidas consumidas.
** @var lfork 			 el tenedor izquierdo del filósofo.
** @var rfork 			 el tenedor derecho del filósofo.
** @var fork 			 un mutex que simboliza un tenedor del problema de cena de los filósofos.
** @var data 			 el acceso a los parámetros de s_data.
*/

typedef struct s_philo
{
	int					id;
	unsigned long		last_meal;
	int					meals_counter;
	int					lfork;
	int					rfork;
	pthread_mutex_t		*fork;
	t_data				*data;

}				t_philo;

/*
 ** =========[ Prototypes ]========
 */

/*
 ** utils.c
 */

long			ft_atol(char const *str);
int				ft_min(int a, int b);
int				ft_max(int a, int b);

/*
 ** sim_utils.c
 */

void			ft_print(t_philo *philo, char const *const a);
void			ft_died(t_data *data);
void			ft_done(t_data *data);
int				ft_check_died(t_philo *philo);
int				ft_check_done(t_philo *philo);

/*
 ** time_utils.c
 */

unsigned long	ft_abs_time(void);
unsigned long	ft_rel_time(unsigned long begin);
void			ft_msleep(unsigned long msec);

/*
 ** simulation.c
 **
 ** @brief      Define each philosopher (threads) life cycle.
 */

/* int  		ft_start_eating(t_philo *philo); */
/* int  		ft_finish_eating(t_philo *philo); */
/* int  		ft_eating(t_philo *philo); */
void			*ft_simulation(void *arg);

/*
 ** simulator.c
 **
 ** @brief      Generate, manage and destroy the simulation required threads.
 */

/* void 		ft_destroy_mutexes(t_philo *philo, t_data *data) */
/* bool 		ft_are_done(t_philo *philo, t_data *data) */
/* int  		ft_monitor(t_philo *philo, t_data *data) */
int				ft_simulator(t_philo *philo, t_data *data);

/*
 ** init.c
 **
 ** @brief      Initialize the C structures.
 */

int				ft_init_philo(t_philo **philo, t_data *data);
int				ft_init_data_mutexes(t_data **data);
int				ft_init_data(t_data **data, int ac, char const *const *av);
int				ft_init(t_philo **p, t_data **d, int ac, char const *const *av);

/*
 ** checkargs.c
 **
 ** @brief      Protect and make sure the user given parameters are valid.
 */

/* bool			ft_is_numeric(char const *str) */
int				ft_check_args(int ac, char const *const *argv);

/*
 ** main.c
 */

/* void			ft_clear_memory(t_philo *philo, t_data *data) */
/* bool			ft_edgecases(int ac, char const *const *argv) */
int				main(int ac, char const *const *argv);

#endif