#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

typedef struct global_data
{
	int count;
	int use;
} global_data;

void *semwait(void *gdata)
{
	global_data *data = (global_data *)gdata;
	while (data->use == 1)
		;
	data->use = 1;
}

void *semsignal(void *gdata)
{
	global_data *data = (global_data *)gdata;
	data->use = 0;
}

// child fonction
void *subchild(void *gdata)
{
	int i = 0;
	int count;
	global_data *data = (global_data *)gdata;

	semwait(data);
	while (i < 99999)
	{
		count = data->count;
		count--;
		data->count = count;
		printf("--SUB = %d\n", data->count);
		i++;
	}
	semsignal(data);
}
void *addchild(void *gdata)
{
	int i = 0;
	int count;
	// get data
	global_data *data = (global_data *)gdata;
	
	semwait(data);
	while (i < 99999)
	{
		count = data->count;
		count++;
		data->count = count;
		printf("++add = %d\n", data->count);
		i++;
	}
	semsignal(data);
}
int main()
{
	pthread_t t1, t2;
	global_data gdata;
	gdata.count = 0;
	gdata.use = 0;

	printf("START do SOME thing.\n");

	pthread_create(&t1, NULL, subchild, (void *)&gdata);
	pthread_create(&t2, NULL, addchild, (void *)&gdata);
	
	// semwait child finished
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	// output global data->count
	printf("global data = %d\n", gdata.count);

	return 0;
}
