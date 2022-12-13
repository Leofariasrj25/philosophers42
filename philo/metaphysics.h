/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaphysics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:09:20 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/12 21:57:25 by lfarias-         ###   ########.fr       */
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
	unsigned int	philo_id;
	unsigned int	n_of_philos;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	unsigned int	min_meals;
	unsigned long	matrix_start;
	unsigned int	permission_to_eat:1;
	unsigned int	ask_permission:1;
	unsigned int	lt_eat;
	unsigned int	state;
	long			ticket_n;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*rfork_mutex;
	pthread_mutex_t	*lfork_mutex;
	pthread_mutex_t	*waiter_lock;
	pthread_mutex_t	*print_mutex;
}	t_philo;

typedef struct s_ideal_table
{
	int				n_of_philos;
	int				n_of_forks;
	t_philo			*philos;
	pthread_t		*waiter;
	pthread_t		*philo_threads;
	pthread_mutex_t	*forks;
}	t_table;

// simulation
int				philo_load_meta(t_philo *philosopher, int *values);
t_philo			*philo_create(int *values);
int				dinner_start(t_table *dinner_table);
int				dinner_end(t_table *dinner_table);
void			*simulation(void *param);

// philo actions
int				philo_sleep(t_philo *philosopher);
int				philo_eat_meal(t_philo *philosopher);
int				philo_take_lfork(t_philo *philosopher);
int				philo_take_rfork(t_philo *philosopher);
int				check_alive(t_philo *philosopher);

// waiter
void			*waiter_serve(void *param);
t_table			*init_waiter_service(void);
unsigned long	get_ticket(void);

// time
unsigned int	elapsed_time_ms(unsigned int timestamp_ms);
int				tstamp_cmp_ms(unsigned int ts1, unsigned int ts2);
unsigned int	getcurrtime_ms(void);

//input
int				get_input(int argc, char **argv, int *values);
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
#endif
