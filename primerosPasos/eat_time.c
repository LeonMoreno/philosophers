#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long int milli(void)
{
	struct timeval t;
	long int time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

int main(void)
{
	long int current;
	long int trans;
	int eat;

	eat = 0;
	current = milli();
	printf("curent = %ld\n", current);
	while ((milli() - current) <= 100)
	{
		printf("transcurrido = %ld\n", (milli() - current));
		eat++;
	}
	printf("eat = %d\n", eat);
	return (0);
}
