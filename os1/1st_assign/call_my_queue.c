#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int r;
	printf("Enqueue 3\n");
	//my_sys_enqueue system call을 하는 부분
	syscall(338,3);
	printf("Enqueue 2\n");
	//my_sys_enqueue system call을 하는 부분
	syscall(338,2);
	printf("Enqueue 1\n");
	//my_sys_enqueue system call을 하는 부분
	syscall(338,1);
	//my_sys_dequeue system call을 하는 부분
	r = syscall(339);
	printf("Dequeue %d\n",r);
	
	return 0;	
}
