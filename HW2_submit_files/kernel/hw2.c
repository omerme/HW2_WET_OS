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
    if(list_empty())
    return sys_get_heaviest_descendant_aux(max_weight, max_pid);
}

asmlinkage long sys_get_heaviest_descendant_aux(long max_weight, max_pid) { ///337
    list_for_each()
}
