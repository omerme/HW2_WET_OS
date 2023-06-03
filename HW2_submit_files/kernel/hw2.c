#include <linux/kernel.h>
#include<linux/sched.h>
#include <linux/list.h>
#include <linux/module.h>

struct task_struct* sys_get_heaviest_descendant_aux(struct task_struct* task);


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
    if(list_empty(&(current->children)))
        return -ECHILD;
    return (long)((sys_get_heaviest_descendant_aux(current))->pid);
}

struct task_struct* sys_get_heaviest_descendant_aux(struct task_struct* task) { ///337
    if(list_empty(&(task->children)))
        return NULL;
    struct list_head* head = &(task->children);
    struct list_head* curr_node;
    struct task_struct* curr_task;
    struct task_struct* max_task = NULL;
    list_for_each(curr_node, head){
        curr_task = list_entry(curr_node, struct task_struct, sibling);
        struct task_struct* max_task_in_subtree = sys_get_heaviest_descendant_aux(curr_task);
        if (max_task_in_subtree == NULL || (curr_task->weight > max_task_in_subtree->weight || (curr_task->weight == max_task_in_subtree->weight && curr_task->pid < max_task_in_subtree->pid)))
            max_task_in_subtree = curr_task;
        if (max_task == NULL || (max_task->weight < max_task_in_subtree->weight || (max_task->weight == max_task_in_subtree->weight && max_task->pid > max_task_in_subtree->pid)))
            max_task = max_task_in_subtree;
    }
    return max_task;
}
