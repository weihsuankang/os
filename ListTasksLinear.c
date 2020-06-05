#include <linux/sched.h>
#include <linux/init.h> //�w�q�F�X�ʪ���l�ƩM�h�X�������禡
#include <linux/kernel.h> //�w�q�F�g�`�Ψ쪺�禡�쫬�Υ����w�q
#include <linux/module.h> //�w�q�F�֤߼Ҳլ������禡�B�ܼƤΥ���
#include <linux/init_task.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List tasks linearly");
MODULE_AUTHOR("team 5");

/* This function is called when the module is loaded. */
int linear_init(void) {
	struct task_struct *task; //Pointer to the task whose information will be printed

	printk(KERN_INFO "Inserting ListTasksLinear\n");	
	
	printk(KERN_INFO "Start listing tasks by linear\n");

	for_each_process(task) {   //for_each_process()���\��O���y��ӵ{�ǳs����C
		printk(KERN_INFO "Task Name: %-20s State: %ld\tProcess ID: %d\n", task -> comm, task -> state, task -> pid);
		//task->comm -> task' name
		//task->state -> task's state (-1 �N�� unrunnable, 0 �N�� runnable, >0 �N�� stopped)
		//task->pid -> task's process ID
	}
	
	printk(KERN_INFO "Stop listing tasks\n");
	return 0;
}

/* This function is called when the module is removed. */
void linear_exit(void) {
	printk(KERN_INFO "Exit List_Tasks_By_Linear\n");
}

module_init(linear_init); // module_init/module_exit���@�δN�O�N�X�ʥH�ʺA���覡�N�X�ʸ��J��֤�
module_exit(linear_exit); //module_init���F��l�Ƹ��J���~,�٦��������O���骺�@��

