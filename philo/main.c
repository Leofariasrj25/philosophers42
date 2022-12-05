/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:24:27 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/05 02:19:44 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int	check_input_size(int argc);
int	get_input(int argc, char **argv, int *values);
int	check_input_values(int argc, char **argv, int *values);

#ifndef U_INT_MAX
# define U_INT_MAX 4294967295
#endif 

// tv_sec seconds since epoch
// usleep(microseconds (1,000,000 of a second)
void	print_status(t_philo *philosopher, char *status)
{
	struct timeval	current_time;
	unsigned long	timestamp;

	pthread_mutex_lock(philosopher->print_mutex);
	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec * 1000) - philosopher->matrix_start;
	printf("[%ld] %d %s\n", timestamp, philosopher->philo_id, status);
	pthread_mutex_unlock(philosopher->print_mutex);
}

void	*simulation(void *param)
{
	t_philo			*philosopher;
	struct timeval	current_time;
	long			lt_eat_msec;
	long			present_time;

	philosopher = (t_philo *) param;
	gettimeofday(&current_time, NULL);
	lt_eat_msec = current_time.tv_sec * 1000;
 	while (1)
	{
		gettimeofday(&current_time, NULL);
		present_time = current_time.tv_sec;
		if ((present_time - lt_eat_msec) < (philosopher->tt_die / 1000))
		{
			print_status(philosopher, "is thinking");
		}
		else
			break ;
	}
	printf("Philosopher %d is dead\n", philosopher->philo_id);
	return (NULL);
}

int	load_values(t_meta *philo_info, int *values)
{
	if (!philo_info || !values)
		return (-1);
	philo_info->n_of_philos = values[0];
	philo_info->tt_die = values[1];
	philo_info->tt_eat = values[2];
	philo_info->tt_sleep = values[3];
	philo_info->min_meals = values[4];
	if (pthread_mutex_init(&philo_info->print_mutex, NULL) != 0)
	{
		put_err_str("{ERROR}: Could not start mutex print");
		return (-1);
	}
	return (0);
}

t_philo	*philo_create(t_meta *philo_info)
{
	unsigned int	i;
	t_philo			*philos;

	philos = malloc(sizeof(t_philo) * philo_info->n_of_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < philo_info->n_of_philos)
	{
		philos[i].philo_id = i;
		philos[i].tt_die = philo_info->tt_die;
		philos[i].tt_eat = philo_info->tt_eat;
		philos[i].tt_sleep = philo_info->tt_sleep;
		philos[i].min_meals = philo_info->min_meals;
		philos[i].state_change = 0;
		philos[i].state = PHILO_THINK; 
		philos[i].lt_eat = 0;
		philos[i].lt_sleep = 0;
		philos[i].print_mutex = &philo_info->print_mutex;
		i++;
	}
	i = 0;
	while (i < philo_info->n_of_philos)
	{
		printf("The philo index is %i and its id is %i\n", i, philos[i].philo_id);
		i++;
	}
	return (philos);
}

pthread_t	**dinner_start(t_philo *philos, t_meta *philo_info, int *op_code)
{
	unsigned int		i;
	struct timeval		start;
	pthread_t			**philo_threads;
	long				timestamp;

	i = 0;
	philo_threads = malloc(sizeof(pthread_t *) * philo_info->n_of_philos);
	if (!philo_threads)
	{
		put_err_str("{ERROR}: malloc malfunction\n");
		*op_code = -1;
		return (NULL);
	}
	gettimeofday(&start, NULL);
	timestamp = start.tv_sec * 1000;
	while (i < philo_info->n_of_philos)
	{
		philos[i].matrix_start = timestamp;
		philo_threads[i] = malloc(sizeof(pthread_t));
		if (pthread_create(philo_threads[i], \
			 NULL, simulation, (void *) &philos[i]) != 0)
		{
			put_err_str("{ERROR}: error during thread creation\n");
			*op_code = -1;
			return (NULL);
		}
		i++;
	}
	return (philo_threads);
}

int dinner_end(t_philo *philos, pthread_t **philo_threads, int philo_size) 
{
	int	i;

	i = 0;
	while (i < philo_size)
	{
		pthread_join(*philo_threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(philos[0].print_mutex);
	free(philos);
	return (0);
}

int	main(int argc, char **argv)
{
	static int	values[5] = {-1, -1, -1, -1, -1};	
	int			op_code;
	t_meta		philo_info;
	t_philo		*philos;
	pthread_t	**philo_threads;

	op_code = get_input(argc, argv, values);
	if (op_code != 0)
		return (op_code);
	op_code = load_values(&philo_info, values);
	printf("Philo number %i\n", philo_info.n_of_philos);
	printf("Philo tt_die %i\n", philo_info.tt_die);
	printf("Philo tt_eat %i\n", philo_info.tt_eat);
	printf("Philo tt_sleep %i\n", philo_info.tt_sleep);
	if (op_code != 0)
		return (op_code);
	philos = philo_create(&philo_info);
	if (philos == NULL)
		return (-4);
	for (unsigned int i = 0; i < philo_info.n_of_philos; i++)
	{
		printf("Philo number %i philo_id is %i\n", i, philos[i].philo_id);
	}
	philo_threads = dinner_start(philos, &philo_info, &op_code); 
	if (op_code != 0)
		return (op_code);
	op_code = dinner_end(philos, philo_threads, philo_info.n_of_philos);
	if (op_code != 0)
		return (op_code);
	return (0);
}

int	get_input(int argc, char **argv, int *values)
{
	char	*err_msg;
	char	*usage;
	int		ret_code;

	usage = "{USAGE}: ./philo <nº of philosophers> <time to die> <time to eat> \
		<time to sleep> [nº of times every philo must eat]\n";
	if (check_input_size(argc))
	{
		err_msg = "{ERROR}: wrong number of arguments\n";
		put_err_str(err_msg);
		put_err_str(usage);
		return (1);
	}
	ret_code = check_input_values(argc, argv, values);	
	if (ret_code == 2)
	{
		err_msg = "{ERROR}: arg(s) must be greater than zero\n"; 
		put_err_str(err_msg);
	}
	if (ret_code == 3)
	{
		err_msg = "{ERROR}: out of bounds integer value\n";
		put_err_str(err_msg);
	}
	return (ret_code);
}

int	check_input_values(int argc, char **argv, int *values)
{
	long long number; 
	int		i;

	i = 1;
	while (i < argc)
	{
		number = ft_atoll(argv[i]);
		if (number <= 0)
			return (2);
		else if (number > U_INT_MAX)
			return (3);
		else
			values[i - 1] = (unsigned int) number;
		i++;
	}
	return (0);
}

int	check_input_size(int argc)
{
	if (!((argc - 1) == 5 || (argc - 1) == 4))
		return (1);
	else
		return (0);
}
