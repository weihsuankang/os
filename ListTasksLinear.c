#include <linux/sched.h>
#include <linux/init.h> //定義了驅動的初始化和退出相關的函式
#include <linux/kernel.h> //定義了經常用到的函式原型及巨集定義
#include <linux/module.h> //定義了核心模組相關的函式、變數及巨集
#include <linux/init_task.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("List tasks linearly");
MODULE_AUTHOR("team 5");

/* This function is called when the module is loaded. */
int linear_init(void) {
	struct task_struct *task; //Pointer to the task whose information will be printed

	printk(KERN_INFO "Inserting ListTasksLinear\n");	
	
	printk(KERN_INFO "Start listing tasks by linear\n");

	for_each_process(task) {   //for_each_process()的功能是掃描整個程序連結串列
		printk(KERN_INFO "Task Name: %-20s State: %ld\tProcess ID: %d\n", task -> comm, task -> state, task -> pid);
		//task->comm -> task' name
		//task->state -> task's state (-1 代表 unrunnable, 0 代表 runnable, >0 代表 stopped)
		//task->pid -> task's process ID
	}
	
	printk(KERN_INFO "Stop listing tasks\n");
	return 0;
}

/* This function is called when the module is removed. */
void linear_exit(void) {
	printk(KERN_INFO "Exit List_Tasks_By_Linear\n");
}

module_init(linear_init); // module_init/module_exit的作用就是將驅動以動態的方式將驅動載入到核心
module_exit(linear_exit); //module_init除了初始化載入之外,還有後期釋放記憶體的作用

