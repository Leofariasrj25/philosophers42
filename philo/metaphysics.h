/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaphysics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:09:20 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/15 20:03:10 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METAPHYSICS_H
# define METAPHYSICS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

# ifndef PHILO_SLEEP
#  define PHILO_SLEEP 1
# endif

# ifndef PHILO_EAT
#  define PHILO_EAT 2
# endif

# ifndef PHILO_THINK
#  define PHILO_THINK 3
# endif

# ifndef PHILO_DEAD
#  define PHILO_DEAD 4
# endif

typedef struct s_thinker
{
	long			philo_id;
	long			n_of_philos;
    long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			min_meals;
	long			matrix_start;
	unsigned int	permission_to_eat:1;
	unsigned int	ask_permission:1;
	unsigned int	lt_eat;
	unsigned int	state;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*rfork_mutex;
	pthread_mutex_t	*lfork_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t *state_mutex;
}	t_philo;

typedef struct s_ideal_table
{
	int				is_dinner_over:1;
	int				n_of_philos;
	int				n_of_forks;
	t_philo			*philos;
	pthread_t		*philo_threads;
	pthread_t		*monitor_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t *dinner_lock;
}	t_table;

// simulation
int				philo_load_meta(t_philo *philosopher, int *values);
t_philo			*philo_create(long *values);
int				dinner_start(t_table *dinner_table);
int				dinner_end(t_table *dinner_table);
void			*simulation(void *param);

// philo actions
int				philo_sleep(t_philo *philosopher);
int				philo_eat_meal(t_philo *philosopher);
int				philo_take_lfork(t_philo *philosopher);
int				philo_take_rfork(t_philo *philosopher);
int				check_alive(t_philo *philosopher);
int				philo_put_forks_down(t_philo *philosopher);

// monitor
int				monitor_start(t_table *dinner_table);
void			*monitor_watch(void *param);

// time
long			elapsed_time_since(unsigned int timestamp_ms);
long			getcurrtime_ms(void);
void			micro_sleep(long duration);

//input
int				get_input(int argc, char **argv, long *values);
long long		ft_atoll(char *str);

// output 
void			print_status(t_philo *philosopher, char *msg);
void			put_str_fd(int fd, char *c);
void			put_err_str(char *c);

// utils
void			*ph_calloc(size_t count, size_t size);
int				test_alloc(void *ptr);
int				mutex_start(pthread_mutex_t *mutex);
int				thread_start(pthread_t *thread, void *(f)(void *), void *p);
void			destroy_all_philos(t_philo *philos, int n_of_philos);
void			destroy_all_forks(pthread_mutex_t *forks, int n_of_forks);
void			destroy_philo_locks(t_philo *philos);
#endif
