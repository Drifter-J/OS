#include <linux/linkage.h> 
#include <linux/kernel.h>
#include <linux/syscalls.h>

#define Num 3

int queue[Num] = { 0 }; // queue global 변수로서의 선언
int count = 0; // 큐에 꽉 차지 않는 이상 인큐를 하기위해서 for loop을 돌릴 때 쓰는 변수 
int rear = 0; // queue의 rear
int front = 0; // queue의 front
int i = 0; // 그냥 temporary 변수

asmlinkage void sys_my_enqueue(int a){
	printk("hello\n");
	// distinguish하기위해서 임의로 추가한 출력 메세지므로 무시해도됨.
	printk("New System Call Saying %d\n", a);
	// printk는 log message 출력하기 위함
	++count;
	if (rear < Num){
		for (i = 0; i<count; i++){
			if (queue[i] == a){
				printk("Error: Value Already Exists\n");
				break;
			}
			else{
				if (i == count - 1){
					queue[rear] = a;
					printk("Enqueue: %d\n", queue[rear]);
					rear++;
				}
			}
		}
	}
	else{
		printk("Error: Queue Overflow\n");
	}
	printk("Queue:\t");
	for (i = 0; i < Num; i++){
		if (queue[i]!=0)
			printk("%d ",queue[i]);
	}
	printk("\n");
}

asmlinkage int sys_my_dequeue(void){
	int temp = 0; // 임시 변수
	if (front == Num){
		printk("Error: No Element in Queue\n");
		return 0;
	}
	else{
		temp = queue[front];
		queue[front] = 0;
		printk("Dequeue: %d\n", temp);
		front++;
	}
	printk("Queue:\t");
	for (i = 0; i < Num; i++){
		if (queue[i] != 0)
			printk("%d ", queue[i]);
	}
	printk("\n");
	return temp;
}
