/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:24:27 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/15 20:01:47 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

int	table_init(t_table *table);

int	main(int argc, char **argv)
{
	long		values[5] = {-1, -1, -1, -1, -1};	
	int			op_code;
	t_table		table;

	op_code = get_input(argc, argv, values);
	if (op_code != 0)
		return (op_code);
	table.philos = philo_create(values);
	if (table.philos == NULL)
		return (-4);
	table_init(&table);
	op_code = dinner_start(&table);
	if (op_code != 0)
		return (op_code);
	op_code = dinner_end(&table);
	if (op_code != 0)
		return (op_code);
	return (0);
}

int	table_init(t_table *table)
{
	table->n_of_philos = table->philos[0].n_of_philos;
	table->n_of_forks = table->philos[0].n_of_philos;
	table->dinner_lock = ph_calloc(1, sizeof(pthread_mutex_t));	
	if (!table->dinner_lock)
	{
		destroy_all_philos(table->philos, table->n_of_philos);
		return (-1);
	}
	return (0);
}
