#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>
#define SIZE 60
// 計數器
int counter = 0;


typedef struct my_pid {
	int pid ;
} my_pid;

// 子執行緒函數
void* child(void *arg) {

	int arry[SIZE][SIZE];
	int *result = calloc( SIZE , sizeof(int) );

	// 取得資料
	my_pid *pid = (my_pid *)arg;
	pid->pid = syscall(SYS_gettid); 
	
	FILE *fin; 
	fin = fopen( "number.txt","rt" );
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			fscanf(fin,"%d",&arry[i][j]);
		}
	}
 	fclose(fin);

	while(counter<=0){
		
	}
	while(counter>0){
		for(int k=0;k<9999;k++){
			for(int i=0;i<SIZE;i++){
				for(int j=0;j<SIZE;j++){
					result[i]+=arry[i][j]*arry[j][0];
				}
			}
		}
		break;
	}

   	pthread_exit((void *) result); // 傳回結果
}

// 主程式
int main() {

	double timeStart, timeEnd;
	pthread_t t1,t2,t3;
	int core;
	void *ret1,*ret2,*ret3; 
	my_pid pid1,pid2,pid3;
	char str1[20],str2[20],str3[20];
	

	printf("MAINPID=%ld\n", syscall(SYS_gettid));

	// 取得CPU核心數
	system("grep -m1 \"cpu cores\" /proc/cpuinfo >CPUINFO");
	FILE *fin; 
	fin = fopen( "./CPUINFO","rt" );

	while(core != 58){
		fscanf(fin,"%c",&core);
	}

	fscanf(fin,"%c",&core);
	fscanf(fin,"%d",&core);
	fclose(fin);

	printf("\n%d\n",core);


	//thread 創建
	pid1.pid = 0;
	pid2.pid = 0;
    pid3.pid = 0;
	pthread_create(&t1, NULL, child, (void*) &pid1);
	pthread_create(&t2, NULL, child, (void*) &pid2);
    pthread_create(&t3, NULL, child, (void*) &pid3);

	//判斷PID
	while(pid1.pid == 0){
	}
	printf("HI, MY_PID=%d\n", pid1.pid);
	sprintf(str1, "taskset -cp %d %d", core-1, pid1.pid);
	system(str1);


	while(pid2.pid == 0){
	}
	printf("HI, MY_PID=%d\n", pid2.pid);
	sprintf(str2, "taskset -cp %d  %d",core-2, pid2.pid);
	system(str2);

    while(pid3.pid == 0){
	}
	printf("HI, MY_PID=%d\n", pid3.pid);
	sprintf(str3, "taskset -cp %d  %d",core-3, pid3.pid);
	system(str3);

	printf("\n輸入1繼續矩陣相乘\n");
	
	scanf("%d",&counter);
        timeStart = clock();
	// 等待子執行緒計算完畢
	pthread_join(t1, &ret1);
	pthread_join(t2, &ret2);
    pthread_join(t3, &ret3);

	// 取得計算結果
	int *result1 = (int *) ret1;
	int *result2 = (int *) ret2;
    int *result3 = (int *) ret3;

	// 輸出計算結果
	for(int i=0;i<SIZE;i++){
		printf("%10d----%10d----%10d\n",result1[i],result2[i],result3[i]);
	}
	printf("\n");
	timeEnd = clock();
	// 輸出花費時間
	printf("total time (clock) = %f s\n",(timeEnd-timeStart)/CLOCKS_PER_SEC);
	// 釋放記憶體
	free(result1);
	free(result2);
    free(result3);
	return 0;
}
