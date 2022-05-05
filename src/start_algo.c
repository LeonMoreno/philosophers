#include "philo.h"

void *ft_pthread(void *arg)
{
	t_state_philo *p;
	pthread_mutex_t *f_r;
	pthread_mutex_t *f_l;
	long int current;
	int	eat;
	
	p = ((t_state_philo *)arg);
	eat = 0;
	current = 0;
	p->born = milli();
	if (p->id == 1)
		f_l = &p->args->mutex[p->args->phi - 1]; 
	else
		f_l = &p->args->mutex[p->id - 2]; 
	f_r = &p->args->mutex[p->id - 1]; 
	if (p->id % 2)
		usleep(15007);
	while (!p->died)
	{
		pthread_mutex_lock(f_l);
		print_msg(arg, p->id, milli() - p->born, "Has taken a Tenedor");
		pthread_mutex_lock(f_r);
		print_msg(arg, p->id, milli() - p->born, "Has taken a Tenedor");
		current = milli();
		p->is_eating = milli();
		print_msg(arg, p->id, milli() - p->born, "is eating");
		while ((milli() - current) < p->args->time_to_eat)
			eat++;
		pthread_mutex_unlock(f_l);
		pthread_mutex_unlock(f_r);
		print_msg(arg, p->id, milli() - p->born, "is Sleeping");
		usleep(p->args->time_to_sleep * 1000);
	}
	return (NULL);
}

void start_mutex(t_args *a)
{
	int	i;

	i = 0;
	
	a->mutex = malloc(sizeof(int) * a->phi);
	if (!a->mutex)
		return ;
	while (i < a->phi)
	{
		pthread_mutex_init(&a->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&a->msg, NULL);
}

void start_philos(t_args *args)
{
	int	i;
	t_state_philo *p;

	i = 0;
	p = malloc(sizeof(t_state_philo) * args->phi);
	if (!p)
		return ;
	start_mutex(args);
	while (i < args->phi)
	{
		p[i].id = i + 1;
		p[i].died = 0;
		p[i].is_eating = milli();
		p[i].args = args;
		pthread_create(&p[i].thread_id, NULL, ft_pthread, &p[i]);
		i++;
	}
	if (!check_live(p))
	{
		printf("Game Over\n");
		return ;
	}
	i = 0;
	while (i < args->phi)
	{
		pthread_join(p[i].thread_id, NULL);
		i++;
	}
	printf("Tiempo transcurrido desde el inicio: %ld\n", milli() - p[0].born);

}
