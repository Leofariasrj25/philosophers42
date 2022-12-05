/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:24:27 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/05 14:53:52 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

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
	if (op_code != 0)
		return (op_code);
	philos = philo_create(&philo_info);
	if (philos == NULL)
		return (-4);
	philo_threads = dinner_start(philos, &philo_info, &op_code); 
	if (op_code != 0)
		return (op_code);
	op_code = dinner_end(philos, philo_threads, philo_info.n_of_philos);
	if (op_code != 0)
		return (op_code);
	return (0);
}

