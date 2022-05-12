/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:31:07 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/12 15:13:48 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_args
{
	int				phi;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nx_eat;
	int				died;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	msg;
	pthread_mutex_t	check_eat;
}	t_args;

typedef struct s_state_philo
{
	int			id;
	pthread_t	thread_id;
	t_args		*args;
	long int	born;
	long int	take_fork;
	long int	is_eating;
	long int	is_sleeping;
	long int	is_thinking;
	int			eat;
	int			xnum_eat;
	long int	current;
}	t_state_philo;

//FT Philosopher pthreads
void	start_philos(t_args *a);
void	*ft_pthread(void *arg);

//FT Utils
long	int	milli(void);
int		check_live(t_state_philo *t);
void	print_msg(t_args *a, int id, long current, char *s);
void	free_all(t_state_philo *p);
#endif
