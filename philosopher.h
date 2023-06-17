/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgutier <frgutier@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:11:12 by frgutier          #+#    #+#             */
/*   Updated: 2023/06/17 11:27:06 by frgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

// Includes
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

// Structures
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

// [Prototypes]

// utils.c
long                ft_atol(const char *str);
int				ft_min(int a, int b);
int				ft_max(int a, int b);

// time_utils.c
unsigned long	ft_abs_time(void);
unsigned long	ft_rel_time(unsigned long begin);
void			ft_msleep(unsigned long msec);

// init.c
int				ft_init_philo(t_philo **philo, t_data *data);
int				ft_init_data_mutexes(t_data **data);
int				ft_init_data(t_data **data, int ac, char const *const *av);
int				ft_init(t_philo **p, t_data **d, int ac, char const *const *av);

// checkargs.c
int				ft_checkargs(int ac, char const *const *av);


#endif