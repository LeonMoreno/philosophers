#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_argu
{
	int	num;
}	t_argu;

typedef struct s_hilo
{
	int	id;
	pthread_t id_hilo;
	t_argu	*argu;
	long t;
	int x;
}	t_hilo;

void *ft_hilo(void *args)
{
	struct timeval ct;
	t_hilo *h;

	h = ((t_hilo *)args);
	printf("Hilo = %d argu_num = %d\n", h->id, h->argu->num);
	gettimeofday(&ct, NULL);
	h->t = 	(ct.tv_sec * 1000) + (ct.tv_usec / 1000);
	h->x = 45 * h->id;
	printf("t = %ld x = %d\n", h->t, h->x);
	return (NULL);
}
/* Aqui estoy viendo como se comparte la memoria entre hilos
 * a cada hilo se le envia la direccion de memoria del index
 * de un array. Este alli escribe, y luego puedo acceder a esta info
 * desde el main().
 * algo importante, q aun no entiendo bien, tanto el heap como
 * el stack de main() son compartidos por lo hilos.
 */

int main(void)
{
	int i;
	t_argu argu;
	t_hilo h[3];

	//h = malloc(sizeof(t_hilo) * 3);
	argu.num = 7;
	i = 0;
	while (i < 3)
	{
		h[i].argu = &argu;
		h[i].id = i;
		pthread_create(&h[i].id_hilo, NULL, ft_hilo, &h[i]);
		i++;
	}
	sleep(2);
	printf("Soy el Hilo Principal x = %d\n", h[0].x);
	printf("Soy el Hilo Principal x = %d\n", h[1].x);
	printf("Soy el Hilo Principal x = %d\n", h[2].x);

	argu.num = 42;
	for(i=0;i < 3;i++)
		pthread_join(h[i].id_hilo, NULL);
	return (0);
}
