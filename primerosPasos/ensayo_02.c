#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *ft_inicio(void *arg)
{
	int i;
	int nr_lines;
	int	fd;
	char buf[] = "Hola mi Leo";

	
	i = 0;
	nr_lines = *(int *)arg;
	printf("El Hilo comienza a ejecutarse\n");
	while(i < nr_lines)
	{
		fd = open("ensayo.txt", O_WRONLY|O_APPEND);
		if (!fd)
			return (NULL); 
		write(fd, &buf, sizeof(buf) - 1);
		write(fd, "\n", 1);
		close(fd);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t hilo_1;
	int	value;

	if(argc != 2)
		{
			printf("No de LIneas no valido\n");
			return (-1);
		}
	value = atoi(argv[1]);
	if (0 != pthread_create(&hilo_1, NULL, ft_inicio, &value))
			return (-1);
	pthread_join(hilo_1, NULL);
	return (0);
}
