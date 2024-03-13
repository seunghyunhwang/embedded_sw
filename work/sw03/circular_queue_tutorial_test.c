#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define __NR_enqueue_syscall	454
#define __NR_dequeue_syscall	455

int main(int argc, char *argv[]){
	int data, result;
	// 인자 개수 검사
	if(argc < 2) { // 최소한 실행 명령어와 'push'/'pop' 필요
		fprintf(stderr, "1Usage: %s <enqueue | dequeue> [data]\n", argv[0]);
		return -1;
	}
	if(!strcmp(argv[1], "enqueue") && argc ==3){
		data = atoi(argv[2]);
		result = syscall(__NR_enqueue_syscall, data);
		if(result!=0){
			fprintf(stderr,"Failed to enqueue!\n");
		}
	} else if (!strcmp(argv[1], "dequeue") && argc == 2){
		result = syscall(__NR_dequeue_syscall);
		if (result != -1){
			printf("Value: %d\n",result);
		}else{
			fprintf(stderr,"Failed to dequeue!\n");
		}
	} else {
		fprintf(stderr,"2Usage : %s <enqueue | dequeue> [data]\n",argv[0]);
		return -1;
	}
	return 0;
}

