#include <linux/linkage.h> 
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/string.h>

asmlinkage int sys_get_tag(int pid, char * my_tag){
	int err_no = 0;
	struct task_struct *target;
	
	read_lock(&tasklist_lock);
        /*task_struct를 얻어오는 과정에서 tasklist에서
        Task의 위치가 바뀌는 것을 방지하기 위해 쓰임*/

	printk("*~*~ Hyem's getProcTag System Call ~*~*\n");
 	printk("\n");

	target = find_task_by_vpid(pid); 
	//finds a task by its virtual pid
	if(!target){
		printk("Corresponding pid task does not exist~!\n");
		err_no = -ESRCH; 
		//(kernel)/include/asm-generic 경로에 들어가면,
		//#define	ESRCH		 3	/* No such process */
		//이런 식으로 있음
		printk("%d error occurs\n", err_no);
		read_unlock(&tasklist_lock); 
		return err_no;
	} else {
		printk("Corresponding pid task exist~!\n");
		
		if((err_no = copy_to_user(my_tag, target->tag, strlen(target->tag))) < 0){
			printk("%d error occurs\n", err_no);
			read_unlock(&tasklist_lock); 
			return err_no;
		} else {
			printk("Set tag exists~!\n");
			printk("Send set task to user~!\n");
			printk("Set tag: %s\n", target->tag);
			printk("Set tag Length: %d\n", strlen(target->tag));
			read_unlock(&tasklist_lock); 
			return 0;
		}
	}
}


