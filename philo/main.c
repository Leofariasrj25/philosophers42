/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:24:27 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/19 22:12:34 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

int	table_init(t_table *table);
int	dinner_setup(t_table *table);

int	main(int argc, char **argv)
{
	static long		values[5] = {-1, -1, -1, -1, -1};	
	int				op_code;
	t_table			table;

	op_code = get_input(argc, argv, values);
	if (op_code != 0)
		return (op_code);
	table.philos = philo_create(values);
	if (table.philos == NULL)
		return (-4);
	table_init(&table);
	dinner_setup(&table);
	op_code = dinner_start(&table);
	if (op_code != 0)
		return (op_code);
	op_code = dinner_end(&table);
	if (op_code != 0)
		return (op_code);
	return (0);
}

int	dinner_setup(t_table *table)
{
	long	total_meals;

	total_meals = -1;
	table->banquet = ph_calloc(1, sizeof(t_dinner));
	if (!table->banquet)
		return (-1);
	table->banquet->dinner_mutex = ph_calloc(1, sizeof(pthread_mutex_t));
	if (!table->banquet->dinner_mutex)
	{
		free(table->banquet);
		return (-1);
	}
	pthread_mutex_init(table->banquet->dinner_mutex, NULL);
	table->banquet->is_over = 0;
	if (table->philos[0].min_meals != -1)
	{	
		total_meals = table->philos[0].min_meals * table->n_of_philos;
		table->banquet->total_meals = total_meals;
	}
	else
		table->banquet->total_meals = total_meals;
	table->banquet->curr_meals = 0;
	return (0);
}

int	table_init(t_table *table)
{
	table->n_of_philos = table->philos[0].n_of_philos;
	table->n_of_forks = table->philos[0].n_of_philos;
	return (0);
}
