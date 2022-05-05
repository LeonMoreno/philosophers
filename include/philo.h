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
	int	time_to_die;
	int	time_to_eat;
	int time_to_sleep;
	int	num_otepmeat;
	pthread_mutex_t *mutex;
	pthread_mutex_t msg;
} t_args;

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
	long int	died;
}	t_state_philo;	

//FT Philosopher pthreads
void start_philos(t_args *a);
void *ft_pthread(void *arg);
void start_mutex(t_args *a);


//FT Utils
long int milli();
int check_live(t_state_philo *t);
void print_msg(t_args *a, int id, long current, char *s);
#endif
