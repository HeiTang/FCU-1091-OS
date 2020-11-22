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

// 子執行緒函數
void* child() {

	int arry[SIZE][SIZE];
	int *result = calloc( SIZE , sizeof(int) );

	printf("HI, MY_PID=%ld\n", syscall(SYS_gettid));
	FILE *fin; // 取得資料
	fin = fopen( "/home/omaga/number.txt","rt" );
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
	//sleep(2);
   	pthread_exit((void *) result); // 傳回結果
}

// 主程式
int main() {

	double timeStart, timeEnd;
	pthread_t t1,t2;
	
	void *ret1,*ret2; 
	printf("MAINPID=%ld\n", syscall(SYS_gettid));


	pthread_create(&t1, NULL, child, NULL);
	pthread_create(&t2, NULL, child, NULL);

	printf("\n輸入1繼續矩陣相乘\n");
	
	scanf("%d",&counter);
        timeStart = clock();
	// 等待子執行緒計算完畢
	pthread_join(t1, &ret1);
	pthread_join(t2, &ret2);
	// 取得計算結果
	int *result1 = (int *) ret1;
	int *result2 = (int *) ret2;
	// 輸出計算結果
	for(int i=0;i<SIZE;i++){
		printf("%10d----%10d\n",result1[i],result2[i]);
	}
	printf("\n");
	timeEnd = clock();
	// 輸出花費時間
	printf("total time (clock) = %f s\n",(timeEnd-timeStart)/CLOCKS_PER_SEC);
	// 釋放記憶體
	free(result1);
	free(result2);
	return 0;
}
