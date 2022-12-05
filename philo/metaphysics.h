/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaphysics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:09:20 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/05 15:40:53 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METAPHYSICS_H
# define METAPHYSICS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

#ifndef PHILO_SLEEP
# define PHILO_SLEEP 1
#endif

#ifndef PHILO_EAT
# define PHILO_EAT 2
#endif

#ifndef PHILO_THINK
# define PHILO_THINK 3
#endif

#ifndef PHILO_DEAD
# define PHILO_DEAD 4
#endif

typedef struct s_platonic_philo
{
	unsigned int	n_of_philos;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	unsigned int	min_meals;
	unsigned long	matrix_start;
	pthread_mutex_t	print_mutex;
}	t_meta;

typedef struct s_thinker
{
	unsigned int	philo_id;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	unsigned int	min_meals;
	unsigned int	lt_eat;
	unsigned int	lt_sleep;
	unsigned int	state_change:1;
	unsigned int	state;
	unsigned long	matrix_start;
	pthread_mutex_t	*print_mutex;
}	t_philo;

typedef struct s_dinning_table
{
	pthread_mutex_t	*forks;
	int				num_of_forks;
	unsigned int	simulation_start;
}	t_table;

// simulation
pthread_t	**dinner_start(t_philo *philos, t_meta *philo_info, int *op_code);
int			dinner_end(t_philo *philos, pthread_t **philo_threads, int philo_size);
void		*simulation(void *param);
t_philo		*philo_create(t_meta *philo_info);

//input
int			get_input(int argc, char **argv, int *values);
int			load_values(t_meta *philo_info, int *values);

// output 
void		print_status(t_philo *philosopher, char *msg);
void		put_str_fd(int fd, char *c);
void		put_err_str(char *c);
long long	ft_atoll(char *str);
#endif
