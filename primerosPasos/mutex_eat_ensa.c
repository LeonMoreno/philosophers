#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	*mutex;
} t_data;

typedef struct s_ens
{
	int	id;
	pthread_t	pth;
	t_data		*f;
}	t_ens;

long int milli(void)
{
	int long current;
	struct timeval t;

	gettimeofday(&t, NULL);
	current = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (current);
}

void *ft_ft(void *arg)
{
	t_ens *e;
	long int ya;
	int eat;
	pthread_mutex_t *f_r;
	pthread_mutex_t *f_l;

	e = ((t_ens *)arg);
	if (e->id == 1)
		f_l = &e->f->mutex[3 -1];
	else
		f_l = &e->f->mutex[e->id - 2];
	f_r = &e->f->mutex[e->id - 1];
	//pthread_mutex_lock(&e->f->mutex);
	printf("Hilo = %d born %ld\n", e->id, milli());
	//printf("Fork_0 = %d \n", *f_l);
	eat = 0;
	pthread_mutex_lock(f_l);
	pthread_mutex_lock(f_r);
	ya = milli();
	printf("milli - ya = %ld\n", milli() - ya);
	while ((milli() - ya) < 200)
		eat++;
	printf("Hilo = %d eat = %d \n", e->id, eat);
	pthread_mutex_unlock(f_l);
	pthread_mutex_unlock(f_r);
	return (NULL);
}

int main(void)
{
	int 	i;
	t_ens	*e;
	t_data	d;

	i = 0;
	e = malloc(sizeof(t_ens) * 3);
	if (!e)
		return -1;
	d.mutex = malloc(sizeof(int) * 3);
	if (!d.mutex)
		return -1;
	while (i < 3)
	{
		pthread_mutex_init(&d.mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		e[i].id = i + 1;
		e[i].f = &d;
		pthread_create(&e[i].pth, NULL, ft_ft, &e[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		pthread_join(e[i].pth, NULL);
		i++;
	}
	return (0);
}


