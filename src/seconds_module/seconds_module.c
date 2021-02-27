#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/jiffies.h>

/*
 * ^ instead of <asm/uaccess.h>
 * https://lkml.org/lkml/2017/9/30/189
 * There seems to be a kernel bug here
*/

/*
 * This code I used for Tuffix makes a whole lot more sense (I didn't write the original logic)
 *
 * https://github.com/mshafae/tuffix/blob/4b362c777044aa92e6da9251e1a1e7fa18b1ddc9/Tuffix/Status.py#L133
*/


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jared Dyreson");

MODULE_DESCRIPTION("proc seconds module");
MODULE_VERSION("0.01");

#define BUFFER_SIZE 128
#define PROC_NAME "seconds"

long init_seconds = 0;

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;
    if(completed){
        completed = 0;
        return 0;
    }
    completed = 1;
    init_seconds = (jiffies / HZ);
    rv = sprintf(buffer, "%lu\n", init_seconds);
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}

static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};


static int __init proc_init(void) {
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    return 0;
}
static void __exit proc_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);

    printk(KERN_INFO "[INFO] Total time taken is %lu\n", ((jiffies / HZ) - init_seconds));
}

module_init(proc_init);
module_exit(proc_exit);
