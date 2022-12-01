/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metaphysics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:09:20 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/01 14:40:13 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METAPHYSICS_H
# define METAPHYSICS_H

#include <pthread.h>

typedef struct s_platonic_philo
{
	int	tt_eat;
	int	tt_die;
	int	tt_think;
	int	tt_sleep;
	int	min_meals;
} t_meta;

typedef struct s_thinker
{
	int philo_id;
	int	tt_eat;
	int	tt_die;
	int	tt_think;
	int	tt_sleep;
	int	min_meals;
} t_philo;

typedef struct s_dinning_table
{
	pthread_mutex_t *forks;
} t_table;
#endif
