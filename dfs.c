#include <linux/sched.h>
#include <linux/init.h> //�w�q�F�X�ʪ���l�ƩM�h�X�������禡 
#include <linux/kernel.h> //�w�q�F�g�`�Ψ쪺�禡�쫬�Υ����w�q 
#include <linux/module.h> //�w�q�F�֤߼Ҳլ������禡�B�ܼƤΥ��� 
#include <linux/init_task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("team 5");

// DFS �`���u���j�M 
void dfs(struct task_struct *task) {
	struct task_struct *child; //Pointer to the next child
	struct list_head *list; //Children
	
	printk(KERN_INFO "Task Name: %-20s State: %ld\tProcess ID: %d\n", task -> comm, task -> state, task -> pid);
	//task->comm -> task' name
	//task->state -> task's state (-1 �N�� unrunnable, 0 �N�� runnable, >0 �N�� stopped)
	//task->pid -> task's process ID
	
	//�@�� for �`���A�Q�ζǤJ�� pos�@���`���ܶq�A�q���Y head�}�l�A�v���V��]next��V�^���� pos �A���ܤS�^�� head
	list_for_each(list, &task -> children) { 
		child = list_entry(list, struct task_struct, sibling); //Get child
		/* child points to the next child in the list */
		//list_for_each�M list_entry�o��ӥ����f�t�ϥδN�i�H�s������쵲��C
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

module_init(dfs_init); // module_init/module_exit���@�δN�O�N�X�ʥH�ʺA���覡�N�X�ʸ��J��֤�
module_exit(dfs_exit); //module_init���F��l�Ƹ��J���~,�٦��������O���骺�@��

