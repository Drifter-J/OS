#include <linux/linkage.h> 
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/string.h>

asmlinkage int sys_set_tag(int pid, char * my_tag, char * pre_tag){
	int err_no = 0;
	char none[] = "NONE";
	struct task_struct *target;
	
	read_lock(&tasklist_lock);
        /*task_struct를 얻어오는 과정에서 tasklist에서
        Task의 위치가 바뀌는 것을 방지하기 위해 쓰임*/

	printk("*~*~ Hyem's setProcTag System Call ~*~*\n");
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

		if(target->tag == 0){
			printk("Previous tag does not exist~!\n");
			
			target->tag = kmalloc(strlen(my_tag), GFP_KERNEL);
			//tag를 malloc해서 가리키게끔

			if((err_no = copy_from_user(target->tag, my_tag, strlen(my_tag))) < 0){
				//write into kernel memory
				printk("%d error occurs\n", err_no);
				read_unlock(&tasklist_lock); 
				return err_no;
			}
								
			printk("Return NONE as previous tag~!\n");
			if((err_no = copy_to_user(pre_tag, none, strlen(none))) < 0){		
				//write into kernel memory
				printk("%d error occurs\n", err_no);
				read_unlock(&tasklist_lock); 
				return err_no;	
			} else {
				printk("Set tag: %s\n", target->tag);
				printk("Set tag Length: %d\n", strlen(target->tag));
			}

			read_unlock(&tasklist_lock); 
			return 0;			 
		} else {
			printk("Previous tag exists~!\n");

			printk("Send previous tag to user~!\n");
			if((err_no = copy_to_user(pre_tag, target->tag, strlen(target->tag))) < 0){
				//write into kernel memory
				printk("%d error occurs\n", err_no);
				read_unlock(&tasklist_lock); 
				return err_no;	
			} else {			
				printk("Previous tag: %s\n", target->tag);
				printk("Previous tag Length: %d\n", strlen(target->tag));
				printk("\n");	
				printk("Return allocated memory of previous tag~!\n");
				//In some sense, freeing allocated memory is like
				//returning memory to the kernel
			//	kfree(target->tag);
				//free previous tag, because it won't be needed after all	
			}
			target->tag = kmalloc(strlen(my_tag), GFP_KERNEL);
			//tag를 malloc
		
			if((err_no = copy_from_user(target->tag, my_tag, strlen(my_tag))) < 0){
				//write into kernel memory
				printk("%d error occurs\n", err_no);
				read_unlock(&tasklist_lock); 
				return err_no;
			}
						
			printk("Set tag: %s\n",target->tag);
			printk("Set tag Length: %d\n", strlen(target->tag));
			
			read_unlock(&tasklist_lock); 
			return 0;		
		}
	}
}

