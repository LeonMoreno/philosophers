#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_args
{
	int phi;
	int *fork;
	int	time_to_die;
	int	time_to_eat;
	int time_to_sleep;
	int	num_otepmeat;
} t_args;

typedef struct s_state_philo
{
	int			id;
	pthread_t	thread_id;
	long int	born;
	long int	take_fork;
	long int	is_eating;
	long int	is_sleeping;
	long int	is_thinking;
	long int	died;
}	t_state_philo;	

//FT Philosopher pthreads
void start_philos(t_args *a);
void *ft_pthread(void *arg);


//FT Utils
long int milli();
#endif
