#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void *ft_hilo(void *args)
{
	struct timeval current_time;

	printf("Comenzo Hilo\n");
	gettimeofday(&current_time, NULL);
	printf("Sec: %ld - microsec %d \n", current_time.tv_sec, current_time.tv_usec);
	return (NULL);
}

int main(void)
{
	int i;
	pthread_t id_hilo[2];

	i = 0;
	while (i < 3)
	{
		pthread_create(&id_hilo[i],NULL,ft_hilo,NULL);
		i++;
	}
	for(i=0;i < 3;i++)
	{
		printf("id del Hilo es = %d\n", id_hilo[i]);
		pthread_join(id_hilo[i], NULL);
	}
	return (0);
}
