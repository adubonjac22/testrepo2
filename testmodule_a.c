#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/sched/signal.h>


// emulacija ps komande za izlistavanje procesa

char buffer[256]; //buffer za printk poruku 

char * get_task_state(long state) //citanje stanja
{
	switch (state) 
	{
		case TASK_RUNNING:
			return "RUNING";
		case TASK_INTERRUPTIBLE:
			return "INTERRUPTIBLE";
		case TASK_UNINTERRUPTIBLE:
			return "UNINTERRUPTIBLE";
		case __TASK_STOPPED:
			return "STOPPED";
		case __TASK_TRACED:
			return "TRACED";
		default:
		{
			sprintf(buffer, "Unknown Type: %ld \n", state);
			return buffer;
		}
	}
}

static int test_tasks_init(void)
{
	struct task_struct *task_list;
	unsigned int process_count = 0;
	pr_info("%s: Init \n",__func__);
	for_each_process(task_list)
	{
		pr_info("Process: %s\t PID:[%d]\t State:%s\n",task_list->comm,task_list->pid, get_task_state(task_list->state));
		process_count++;
	}
	pr_info("Num of processes: %u\n",process_count);
	return 0;
}

static void test_tasks_exit(void)
{
	pr_info("%s: Exit",__func__);
}
MODULE_LICENSE("GPL");
module_init(test_tasks_init);
module_exit(test_tasks_exit);