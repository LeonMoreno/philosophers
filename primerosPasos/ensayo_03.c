#include <pthread.h>
#include <stdio.h>

typedef struct s_hilo
{
	int num;
	pthread_mutex_t lock;
} t_hilo;

void *ft_incremento(void *hilo_t)
{
	t_hilo *xx;
	int	i;
	
	i = 0;
	xx  = (t_hilo *)hilo_t;
	pthread_mutex_lock(&xx->lock);
	while (i++ < 10000)
		xx->num++;
	pthread_mutex_unlock(&xx->lock);
	return (NULL);
}

void *ft_decremento(void *hilo_t)
{
	t_hilo *xx;
	int i;

	i = 0;
	xx  = (t_hilo *)hilo_t;
	pthread_mutex_lock(&xx->lock);
	printf("Dir en DECREME lock %p\n", &xx->lock);
	while (i++ < 10000)
		xx->num--;
	pthread_mutex_unlock(&xx->lock);
	return (NULL);
}

int main(void)
{
	t_hilo hilo_t;
	pthread_t hilo;
	pthread_t hilo_02;

	hilo_t.num = 900;
	pthread_mutex_init(&hilo_t.lock, NULL);
	printf("Dir en MAIN lock %p\n", &hilo_t.lock);
	if (0 != pthread_create(&hilo, NULL, ft_incremento, &hilo_t))
		return (-1);	
	if (0 != pthread_create(&hilo_02, NULL, ft_decremento, &hilo_t))
		return (-1);	
	pthread_join(hilo, NULL);
	pthread_join(hilo_02, NULL);
	printf("Valor final de NUM = %d\n", hilo_t.num);
	return (0);
}
