#include <linux/sched.h>
#include <linux/init.h> //定義了驅動的初始化和退出相關的函式 
#include <linux/kernel.h> //定義了經常用到的函式原型及巨集定義 
#include <linux/module.h> //定義了核心模組相關的函式、變數及巨集 
#include <linux/init_task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("team 5");

// DFS 深度優先搜尋 
void dfs(struct task_struct *task) {
	struct task_struct *child; //Pointer to the next child
	struct list_head *list; //Children
	
	printk(KERN_INFO "Task Name: %-20s State: %ld\tProcess ID: %d\n", task -> comm, task -> state, task -> pid);
	//task->comm -> task' name
	//task->state -> task's state (-1 代表 unrunnable, 0 代表 runnable, >0 代表 stopped)
	//task->pid -> task's process ID
	
	//一個 for 循環，利用傳入的 pos作為循環變量，從表頭 head開始，逐項向後（next方向）移動 pos ，直至又回到 head
	list_for_each(list, &task -> children) { 
		child = list_entry(list, struct task_struct, sibling); //Get child
		/* child points to the next child in the list */
		//list_for_each和 list_entry這兩個巨集搭配使用就可以存取整個鏈結串列
		dfs(child); //DFS from child
	}
}

/* This function is called when the module is loaded. */
int dfs_init(void) {
	
	printk(KERN_INFO "Start listing tasks by DFS\n");
	
	dfs(&init_task); //DFS starting init_task
	
	printk(KERN_INFO "Stop listing tasks\n");
	return 0;
}

/* This function is called when the module is removed. */
void dfs_exit(void) {
	printk(KERN_INFO "exit List_Tasks_by_DFS\n");
}

module_init(dfs_init); // module_init/module_exit的作用就是將驅動以動態的方式將驅動載入到核心
module_exit(dfs_exit); //module_init除了初始化載入之外,還有後期釋放記憶體的作用

