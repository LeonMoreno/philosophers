/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoreno <lmoreno@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:31:07 by lmoreno           #+#    #+#             */
/*   Updated: 2022/05/14 15:55:09 by lmoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_args
{
	int				phi;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nx_eat;
	int				died;
	int				brek;
	sem_t			*forks;
	sem_t			*msg;
	sem_t			*check_e;
}	t_args;

typedef struct s_state_philo
{
	int				id;
	pid_t			proc_id;
	pthread_t		thread_id;
	t_args			*args;
	long int		born;
	long int		take_fork;
	long int		is_eating;
	long int		is_sleeping;
	long int		is_thinking;
	int				eat;
	int				xnum_eat;
	long int		current;
}	t_state_philo;

//FT Philosopher pthreads
void	start_philos(t_args *a);
void	ft_procstart(t_state_philo *p);

//FT Utils
long	int	milli(void);
void	*check_live(void *philo);
void	print_msg(t_args *a, int id, long current, char *s);
void	free_all(t_state_philo *p);
#endif
