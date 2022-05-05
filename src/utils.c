#include "philo.h"

long int  milli(void)
{
	int long c_time;
	struct timeval t;

	gettimeofday(&t, NULL);
	c_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (c_time);
}

int check_live(t_state_philo *t)
{
	int i;

	while(1)
	{	
		i = 0;
		while (i < t->args->phi)
		{
			if ((milli() - t[i].is_eating) > t->args->time_to_die)
			{
				t[i].died = 1;
				printf("%ld MURIO HILO %d\n", milli() - t[i].is_eating, t[i].id);
				return (0);
			}	
			i++;
		}
	}
	return (1);
}

void print_msg(t_args *a, int id, long current, char *s)
{
	pthread_mutex_lock(&a->msg);
	printf("%ld %d %s\n", current, id, s);
	pthread_mutex_unlock(&a->msg);
}

