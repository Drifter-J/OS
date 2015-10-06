#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
	int pid_num, is_error = 0;
	char * my_tag;
	char * pre_tag;

	my_tag = (char*) malloc(30);
	pre_tag = (char*) malloc(30);

	printf("PID: ");
	scanf("%d", &pid_num);

	printf("Input tag: ");
	scanf("%s", my_tag);

	is_error = syscall(338, pid_num, my_tag, pre_tag);
	
	if(is_error < 0){
		// sys_set_tag 부분을 보면, 어떤 에러든지간에 
		//error를 음수로 세팅해 return하게끔 되어 있다.   
		printf("PID %d does not exist~!\n", pid_num);
	} else {
		printf("Tag inserted successfully~!\n");
		printf("Previous tag was: %s\n", pre_tag);
	}

	free(my_tag);
	free(pre_tag);

	return 0;
}
