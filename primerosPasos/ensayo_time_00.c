#include <sys/time.h>
#include <stdio.h>

int main(void)
{
	struct timeval time;
	long int current;
	long int timestp;

	gettimeofday(&time, NULL);
	current = time.tv_sec * 1000;
	printf("current = %lu\n", current);
	timestp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	printf("timestp = %lu\n", timestp);
	return (0);
}
