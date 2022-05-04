#include "philo.h"

void *ft_pthread(void *arg)
{
	t_state_philo *p;
	int *f_r;
	int *f_l;
	long int current;
	int	eat;
	
	p = ((t_state_philo *)arg);
	eat = 0;
	current = 0;
	p->born = milli();
	if (p->id == 1)
		f_l = &p->args->fork[p->args->phi - 1]; 
	else
		f_l = &p->args->fork[p->id - 2]; 
	f_r = &p->args->fork[p->id - 1]; 
	pthread_mutex_lock(f_l);
	if (*f_l == 0 && *f_r == 0)
	{
		current = milli();
		*f_l = 1;
		printf("%ld %d Has taken a fork\n", milli() - current, p->id);
		*f_r = 1;
		printf("%ld %d Has taken a fork\n", milli() - current, p->id);
		printf("%ld %d is eating\n", milli() - current, p->id);
		while ((milli() - current) < p->args->time_to_eat)
			eat++;
		printf("Total EAT por %d = %d\n", p->id, eat);
		*f_l = 0;
		*f_r = 0;
	}
	pthread_mutex_unlock(f_l);
	printf("%ld %d is is Sleeping\n", milli() - current, p->id);
	usleep(p->args->time_to_sleep * 1000);
	return (NULL);
}

void start_forks(t_args *a)
{
	int	i;

	i = 0;
	
	a->fork = malloc(sizeof(int) * a->phi);
	if (!a->fork)
		return ;
	while (i < a->phi)
	{
		a->fork[i] = 0;
		i++;
	}
}

void start_philos(t_args *args)
{
	int	i;
	t_state_philo *p;

	i = 0;
	p = malloc(sizeof(t_state_philo) * args->phi);
	if (!p)
		return ;
	start_forks(args);
	pthread_mutex_init(&args->mutex, NULL);
	while (i < args->phi)
	{
		p[i].id = i + 1;
		p[i].args = args;
		pthread_create(&p[i].thread_id, NULL, ft_pthread, &p[i]);
		i++;
	}
	i = 0;
	while (i < args->phi)
	{
		pthread_join(p[i].thread_id, NULL);
		i++;
	}
	printf("Tiempo transcurrido desde el inicio: %ld\n", milli() - p[0].born);

}
