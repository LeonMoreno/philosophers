#include "philo.h"

void *ft_pthread(void *arg)
{
	t_state_philo *p;
	
	p = ((t_state_philo *)arg);
	printf("Hola soy el Hilo No: %d\n", p->id);
	p->born = milli();
	printf("Naci hace: %ld\n", p->born);
	return (NULL);
}

void start_philos(t_args *args)
{
	int	i;
	t_args *a;
	t_state_philo *p;

	i = 0;
	a = args;
	printf("Acceso ARGS directo No phi %d\n", args->phi);
	p = malloc(sizeof(t_state_philo) * a->phi);
	if (!p)
		return ;
	while (i < a->phi)
	{
		p[i].id = i + 1;
		pthread_create(&p[i].thread_id, NULL, ft_pthread, &p[i]);
		i++;
	}
	i = 0;
	while (i < a->phi)
	{
		pthread_join(p[i].thread_id, NULL);
		i++;
	}
	sleep(1);
	printf("Tiempo transcurrido desde el inicio: %ld\n", milli() - p[0].born);
}
