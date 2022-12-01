/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:24:27 by lfarias-          #+#    #+#             */
/*   Updated: 2022/12/01 19:52:20 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metaphysics.h"

int	check_input_size(int argc);
int	check_input(int argc, char **argv);
int	check_input_values(int argc, char **argv);

#ifndef U_INT_MAX
# define U_INT_MAX 4294967295
#endif 

int	main(int argc, char **argv)
{
	int	error;
	
	error = check_input(argc, argv);
	if (error != 0)
		return (error);
	return (0);
}

int	check_input(int argc, char **argv)
{
	char	*err_msg;
	char	*usage;

	usage = "{USAGE}: ./philo <nº of philosophers> <time to die> <time to eat> \
		<time to sleep> [nº of times every philo must eat]\n";
	if (check_input_size(argc))
	{
		err_msg = "{ERROR}: wrong number of arguments\n";
		put_err_str(err_msg);
		put_err_str(usage);
		return (1);
	}
	if (check_input_values(argc, argv) == 2)
	{
		err_msg = "{ERROR}: arg(s) must be greater than zero\n"; 
		put_err_str(err_msg);
		return (2);
	}
	if (check_input_values(argc, argv) == 3)
	{
		err_msg = "{ERROR}: out of bounds integer value\n";
		put_err_str(err_msg);
		return (3);
	}
	return (0);
}

int	check_input_values(int argc, char **argv)
{
	long long number; 
	int		i;

	i = 1;
	while (i < argc)
	{
		number = ft_atoll(argv[i]);
		if (number <= 0)
			return (2);
		if (number <= 0 || number > U_INT_MAX)
			return (3);
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
