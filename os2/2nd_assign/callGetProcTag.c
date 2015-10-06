#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int pid_num, is_error = 0;
	char * pid_tag;

	pid_tag = (char*) malloc(30);
	
	printf("PID: ");
	scanf("%d", &pid_num);
	
	is_error = syscall(339, pid_num, pid_tag);
	
	if(is_error < 0){
		printf("PID %d does not exist~!", pid_num);
	} else {
		printf("Corresponding pid tag is: %s\n", pid_tag);
	}

	free(pid_tag);
	
	return 0;
}

