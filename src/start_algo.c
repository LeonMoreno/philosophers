#include "philo.h"

void *ft_pthread(void *arg)
{
	t_state_philo *p;
	
	p = ((t_state_philo *)arg);
	printf("Hola soy el Hilo No: %d\n", p->[0]->id);
	printf("DIR p : %p\n", p);
	return (NULL);
}

void start_philos(t_args *args)
{
	int	i;
	int j;
	t_args *a;
	t_state_philo *p;

	i = 0;
	j = 1;
	a = args;
	p = malloc(sizeof(t_state_philo) * a->phi);
	if (!p)
		return ;
	while (i < a->phi)
	{
		p[i].id = i;
		pthread_create(&p[i].thread_id, NULL, ft_pthread, &p);
		p->born = milli();
		i++;
	}
	i = 0;
	while (i < a->phi)
	{
		pthread_join(p[i].thread_id, NULL);
		i++;
	}
	printf("DIR p PRINCIPAL : %p\n", &p);
}
