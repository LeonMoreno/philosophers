#include "philo.h"

long int  milli(void)
{
	int long c_time;
	struct timeval t;

	gettimeofday(&t, NULL);
	c_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (c_time);
}
