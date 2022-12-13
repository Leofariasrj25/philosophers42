/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:24:27 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/12 21:52:15 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

int	main(int argc, char **argv)
{
	static int	values[5] = {-1, -1, -1, -1, -1};	
	int			op_code;
	t_table		table;

	op_code = get_input(argc, argv, values);
	if (op_code != 0)
		return (op_code);
	table.philos = philo_create(values);
	if (table.philos == NULL)
		return (-4);
	op_code = dinner_start(&table);
	if (op_code != 0)
		return (op_code);
	op_code = dinner_end(&table);
	if (op_code != 0)
		return (op_code);
	return (0);
}
