#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int *fork;
	pthread_mutex_t	mutex;
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
	int *f_r;
	int *f_l;

	e = ((t_ens *)arg);
	if (e->id == 1)
		f_l = &e->f->fork[3 -1];
	else
		f_l = &e->f->fork[e->id - 2];
	f_r = &e->f->fork[e->id - 1];
	pthread_mutex_lock(&e->f->mutex);
	printf("Hilo = %d born %ld\n", e->id, milli());
	//printf("Fork_0 = %d \n", *f_l);
	eat = 0;
	if (*f_l == 0 && *f_r == 0)
	{
		*f_l = 1;
		*f_r = 1;
		ya = milli();
		printf("milli - ya = %ld\n", milli() - ya);
		while ((milli() - ya) < 200)
			eat++;
		printf("Hilo = %d eat = %d \n", e->id, eat);
		*f_l = 0;
		*f_r = 0;
	}
	pthread_mutex_unlock(&e->f->mutex);
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
	d.fork = malloc(sizeof(t_data) * 3);
	if (!d.fork)
		return -1;
	d.fork[0] = 0;
	d.fork[1] = 0;
	d.fork[2] = 0;
	pthread_mutex_init(&d.mutex, NULL);
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


