#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

typedef struct global_data{
	int count;
	int turn;
	bool flag[2];
}global_data;

void *subchild(void *gdata){
	int i = 0;
	int count;
	global_data *data = (global_data*)gdata;

	do{
		data->flag[0]=true;
		data->turn = 1;
		while(data->flag[1]&&data->turn==1);
		count = data->count;
		count--;
		data->count= count;
		printf("-- SUB = %d\n",data->count);
		i++;
		data->flag[0]=false;
	}while(i<99999);

}
void *addchild(void *gdata){
	int i = 0;
	int count;
	global_data *data = (global_data*)gdata;

	do{
		data->flag[1]=true;
		data->turn = 0;
		while(data->flag[0]&&data->turn==0);
		count = data->count;
		count++;
		data->count= count;
		printf("++ ADD = %d\n",data->count);
		i++;
		data->flag[1]=false;
	}while(i<99999);

}
int main(){
	pthread_t t1,t2;
	global_data gdata;
	gdata.count = 0;
	printf("START do SOME thing\n");
	
	pthread_create(&t1,NULL,subchild,(void*)&gdata)	;
	pthread_create(&t2,NULL,addchild,(void*)&gdata)	;

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	printf("global data = %d\n",gdata.count);

	return 0;
}
