#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_p
{
	pthread_mutex_t	lock;
}	t_p;

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void *go1(void *p)
{
	char *str;
	int i;
	t_p *pp;

	i = 0;
	pp = (t_p *)p;
	str = "Hilo 1: Hola mi leo? \n";
	//pthread_mutex_lock(&ppp->lock);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	//pthread_mutex_unlock(&ppp->lock);
	return (NULL);
}

int main(void)
{
	pthread_t	id1;
	pthread_t	id2;
	t_p			p;

	pthread_mutex_init(&p.lock, NULL);
    pthread_create(&id1, NULL, go1, &p);
    pthread_create(&id2, NULL, go1, &p);
    sleep(1);	
	return (0);
}
