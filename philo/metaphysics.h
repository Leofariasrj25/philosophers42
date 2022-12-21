/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaphysics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:09:20 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/21 18:39:20 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METAPHYSICS_H
# define METAPHYSICS_H

# include <pthread.h>
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

# ifndef MATRIX_END
#  define MATRIX_END 42
# endif

typedef struct s_philo_dinner
{
	pthread_mutex_t	*dinner_mutex;
	int				curr_meals;
	int				total_meals;
	int				is_over;	
}	t_dinner;

typedef struct s_thinker
{
	long			philo_id;
	long			n_of_philos;
	long			tt_die;
	long			tt_eat;
	long			tt_sleep;
	long			n_of_meals;
	long			min_meals;
	long			matrix_start;
	long			lt_eat;
	unsigned int	state;
	t_dinner		*banquet;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*rfork_mutex;
	pthread_mutex_t	*lfork_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*state_mutex;
}	t_philo;

typedef struct s_ideal_table
{
	t_dinner		*banquet;
	int				n_of_philos;
	int				n_of_forks;
	t_philo			*philos;
	pthread_t		*philo_threads;
	pthread_t		*monitor_thread;
	pthread_mutex_t	*forks;
}	t_table;

// simulation
int				philo_load_meta(t_philo *philosopher, int *values);
t_philo			*philo_create(long *values);
int				dinner_start(t_table *dinner_table);
int				dinner_end(t_table *dinner_table);
int				check_is_dinner_over(t_philo *philo);
void			*simulation(void *param);

// philo actions
int				philo_sleep(t_philo *philosopher);
int				philo_eat_meal(t_philo *philosopher);
int				philo_take_forks(t_philo *philosopher);
int				check_alive(t_philo *philosopher);
int				philo_put_forks_down(t_philo *philosopher);

// time
long			get_timestamp_ms(long time_start_ms);
long			get_currtime_ms(void);
void			smart_sleep(long duration);
int				micro_sleep(long duration, t_philo *philosopher);

//input
int				get_input(int argc, char **argv, long *values);
long long		*ft_atoll(const char *str);

// output 
void			print_status(t_philo *philosopher, char *msg, int code);
void			put_str_fd(int fd, char *c);
void			put_err_str(char *c);

// utils
void			*ph_calloc(size_t count, size_t size);
int				mutex_start(pthread_mutex_t *mutex);
int				thread_start(pthread_t *thread, void *(f)(void *), void *p);
void			destroy_all_philos(t_philo *philos, int n_of_philos);
void			destroy_all_forks(pthread_mutex_t *forks, int n_of_forks);
void			destroy_philo_locks(t_philo *philos);
void			destroy_table(t_table *table);

// junk
int				has_forks(t_philo *philosopher);
int				check_total_meals(t_philo *philosopher);
int				add_total_meals(t_philo *philosopher);
long			get_checkpoint_ms(t_philo *philosopher);
#endif
