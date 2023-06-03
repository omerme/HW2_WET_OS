#include <linux/kernel.h>
#include<linux/sched.h>
#include <linux/list.h>
#include <linux/module.h>

asmlinkage long sys_hello(void) { //333
 printk("Hello, World!\n");
 return 0;
}

asmlinkage long sys_set_weight(int weight) { ///334
    if (weight < 0)
        return -EINVAL;
    current->weight = weight;
    return 0;
}

asmlinkage long sys_get_weight(void) { ///335
    return current->weight;
}

asmlinkage long sys_get_ancestor_sum(void) { ///336
    long sum = 0;
    struct task_struct* cur_task = current;
    while (cur_task->pid != 1){
        sum += cur_task->weight;
        cur_task = cur_task->parent;
    }
    return sum;
}

asmlinkage long sys_get_heaviest_descendant(void) { ///337
    long max_weight = -1;
    long max_weight_pid = 0;
    if(list_empty(&(current->children))
        return -ECHILD;
    return sys_get_heaviest_descendant_aux(max_weight, max_pid);
}

asmlinkage struct task_struct* sys_get_heaviest_descendant_aux(struct task_struct* task, long max_weight, long max_pid) { ///337
    struct list_head* head = &(task->children);
    struct list_head* curr_node;
    struct task_struct* curr_task;

    list_for_each(curr_node, head){
        curr_task = list_entry(curr_node, struct task_struct, sibling);
        struct task_struct* max_node_in_subtree = sys_get_heaviest_descendant_aux(curr_task->children);

        if (curr_task->weight > max_weight || (curr_task->weight == max_weight && curr_task->pid < max_pid)){
            max_weight = curr_task->weight;
            max_pid = curr_task->pid;
        }


    }
}

          0
     2         1
 7      0    7    0